import struct
import os
import json
import subprocess
import time
from PySide6.QtCore import QByteArray
from PathManager import PathManager
from PySide6.QtCore import QThread, Signal,QObject
from PySide6.QtNetwork import QTcpServer, QHostAddress
from PySide6.QtCore import QThread, Signal

class mTcpIp(QObject):
    IPAdder = '127.0.0.1'
    connectsignal = Signal()
    receivedBytes = Signal(bytes)
    
    def __init__(self, Port) -> None:
        super().__init__()
        self.clientcounter = 0
        self.server = QTcpServer(self)
        self.server.listen(QHostAddress(self.IPAdder),int(Port))
        self.server.newConnection.connect(self.handle_new_connection)
        self.port = Port
        # 次に受信するデータのサイズ
        self.pending_data_size = None  
        # ヘッダーを期待しているかどうかのフラグ
        self.expecting_header = True  

    def handle_new_connection(self):
        if self.clientcounter == 0:
            self.clientcounter += 1
            self.client = self.server.nextPendingConnection()
            self.client.readyRead.connect(self.read_data)  
            self.connectsignal.emit()
            print(self.port)

    def receivedHeader(self):
        if self.client.bytesAvailable() < 8:
            return
        header = self.client.read(8)
        self.pending_data_size = struct.unpack('<Q', header.data())[0]
        self.expecting_header = False
    
    def receivedData(self):
        if self.client.bytesAvailable() < self.pending_data_size:
            return
        data = self.client.read(self.pending_data_size)
        self.receivedBytes.emit(data)
        self.expecting_header = True      

    def read_data(self):
        if self.expecting_header:
            self.receivedHeader()
        else:
            self.receivedData()
            
    def send_data(self, data):
        if self.clientcounter == 1:
            self.client.write(data)

    def is_connected(self):
        # TCP通信が接続されているかどうかを返す
        return self.clientcounter > 0


class RuntimeMonitorThread(QThread):
    runtime_crashed = Signal()  # ランタイムがクラッシュしたことを通知するシグナル
    
    def __init__(self, process, check_interval=1):
        super(RuntimeMonitorThread, self).__init__()
        self.process = process
        self.check_interval = check_interval
        self.running = True
        

    def run(self):
        while self.running:
            time.sleep(self.check_interval)
            if self.process and self.process.poll() is not None:
                # プロセスがクラッシュした
                self.runtime_crashed.emit()
                break

    def stop(self):
        self.running = False


class IPCManager(QObject):
    __instance = None    
    runtime_terminate = Signal()
    def __new__(cls):
        if cls.__instance is None:
            # インスタンスが存在しない場合にのみインスタンスを作成する
            cls.__instance = super(IPCManager, cls).__new__(cls)
            # モニタースレッドのインスタンスを保持する変数
            cls.monitor_thread = None
            # ランタイムプロセスの情報を保持する変数
            cls.runtime_process = None
            # TCPIPをポート11111で開く
            cls.modeltcp = mTcpIp(11111)
            #　データを受け取るとReceveDataを呼び出す
            cls.modeltcp.receivedBytes.connect(cls.__instance.ReceveData)
            # コールバック関数を格納する辞書
            cls.callbackdict = dict()
            # 接続されたかどうかのフラグ
            cls.modeltcp.connectsignal.connect(cls.__instance.is_connected)
            # コマンドリストを読み込む
            cls.commandlist = cls.LoadIPCCommandList(cls.__instance)
            # 接続されているかどうかのフラグ
            cls.isconnected = False
            
        return cls.__instance
    
    def LoadIPCCommandList(self):
        # JSONファイルのパスを取得
        path = os.path.join(PathManager.ApplicationPath, "config", "networkcommandlist.json")
        # JSONファイルを読み込み
        with open(path, "r", encoding='utf-8') as json_file:
            command_data = json.load(json_file)
        # コマンドのidとnameを辞書で紐づける
        command_dict = {item["name"]:item["id"] for item in command_data["commands"]}
        return command_dict

    def __init__(self) -> None:
        pass

    def SendData(self,datasize:int,command:int,data:bytes):
        #データサイズ、コマンド、データの順になるようにする
        header = struct.pack('<Q',datasize + 4) #コマンドのint型４バイト分を足したサイズ
        #ヘッダーを送信
        self.modeltcp.send_data(header)
        #データを送信
        self.modeltcp.send_data(struct.pack('<I',command) + data)

    def RegisterReceveDataCallBack(self,command,func):
        self.callbackdict[command] = func

    def ReceveData(self, data: QByteArray):
        if len(data.data()) < 4:#コマンドがあるか確認
            raise ValueError("data length must be at least 4 bytes")
        bytedata = data.data()
        command = struct.unpack_from('<I', bytedata[:4])[0]
        print(command)
        jsonstr = bytedata[4:].decode('utf-16le')
        print(jsonstr)
        if command in self.callbackdict:
            self.callbackdict[command](jsonstr)

    def is_connected(self):
        self.isconnected = True

    def start_runtime(self, command):
        try:
            # ランタイムプロセスの起動
            self.runtimecommand = command
            self.runtime_process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            self.monitor_thread = RuntimeMonitorThread(self.runtime_process)
            self.monitor_thread.runtime_crashed.connect(self.on_runtime_crashed)
            self.monitor_thread.start()
        except Exception as e:
            print("ランタイム起動エラー:", e)

    def on_runtime_crashed(self):
        print("ランタイムがクラッシュしました。再起動します。")
        self.start_runtime(self.runtimecommand)
        # 再起動ロジックをここに記述

    def shutdown(self):
        # RuntimeMonitorThreadを停止
        if self.monitor_thread is not None:
            self.monitor_thread.stop()
            self.monitor_thread.wait()  # スレッドの終了を待機

        # mTcpIpサーバーを閉じる
        if self.modeltcp is not None and self.modeltcp.server.isListening():
            self.modeltcp.server.close()

        # ランタイムプロセスを終了
        if self.runtime_process is not None:
            self.SendData(0,999,bytes())