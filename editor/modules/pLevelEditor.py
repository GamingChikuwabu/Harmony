from PySide6.QtCore import QSettings,Qt,QByteArray
import IPresenter
import ModuleManager
from LevelEditor.view.vLevelEditor import vLevelEditor
from IPCManager import IPCManager
import struct
import json

@IPresenter.register("LevelEditor")
class pLevelEditor(IPresenter.IPresenter):
    def __init__(self) -> None:
        super().__init__()
        self.IPC = IPCManager()
    
    def init_data(self):
        return super().init_data()
    
    def init_UI(self):
        self.levelwindow = vLevelEditor("LevelEditor")
        mainwindow = ModuleManager.manager.get_module("MainWindow")
        mainwindow.mainwindow.addDockWidget(Qt.LeftDockWidgetArea,self.levelwindow)
        return super().init_UI()
    
    def Init_After_Runtime(self):
        self.levelwindow.resizeSignal.connect(self.frameResize)
        self.frameResize()
        return super().Init_After_Runtime()
    
    def Terminate(self, setting: QSettings):
        return super().Terminate(setting)
    
    def frameResize(self):
        # ウィンドウIDを取得
        window_id = self.levelwindow.frame.winId()
        # JSON文字列を作成
        jsonStr = json.dumps({"window_id": window_id})
        # JSON文字列をUTF-16でエンコード
        encoded_jsonStr = jsonStr.encode("utf-16")
        # エンコードされたデータの長さを取得
        data_length = len(encoded_jsonStr)
        # データを送信
        self.IPC.SendData(data_length, self.IPC.commandlist["LevelEditorMakeChild"], encoded_jsonStr)
