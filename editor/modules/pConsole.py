from PySide6.QtCore import QSettings,Qt,QByteArray
import IPresenter
import ModuleManager
from Console.view.vConsole import vConsole
from IPCManager import IPCManager

@IPresenter.register("Console")
class pConsole(IPresenter.IPresenter):
    def __init__(self) -> None:
        super().__init__()
        self.IPC = IPCManager()
        self.IPC.RegisterReceveDataCallBack(self.IPC.commandlist.get("SendLog"),self.PrintRuntimeLog)
    
    def init_data(self):
        return super().init_data()
    
    def init_UI(self):
        self.consolewindow = vConsole("Console")
        mainwindow = ModuleManager.manager.get_module("MainWindow")
        mainwindow.mainwindow.addDockWidget(Qt.LeftDockWidgetArea,self.consolewindow)
        return super().init_UI()
    
    def Init_After_Runtime(self):
        self.IPC
        return super().Init_After_Runtime()
    
    def deserialize_UI(self, setting: QSettings):
        return super().deserialize_UI(setting)
    
    def Terminate(self, setting: QSettings):
        return super().Terminate(setting)
    
    def PrintLog(self,Type,message,Color = None):
        self.consolewindow.addLog(Type,message,Color)
    
    def PrintRuntimeLog(self, data_bytes):
        try:
            raw_data = data_bytes
            # メッセージと色名をUTF-8としてデコード
            # マルチバイト文字セットを考慮してデコード
            message = raw_data[:246].decode('utf-8','ignore').rstrip('\x00')
            color_name = raw_data[246:256].decode('utf-8','ignore').rstrip('\x00')
            # ログを出力
            self.PrintLog("engine", message, color_name)
        except Exception as e:
            print(f"Error in __PrintRuntimeLog: {e}")