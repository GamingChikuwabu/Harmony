from PySide6.QtCore import QSettings,Qt,QByteArray
import IPresenter
import ModuleManager
from Console.view.vConsole import vConsole
from IPCManager import IPCManager
import json

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
    
    def PrintRuntimeLog(self, jsonStr:str):
        try:
            data = json.loads(jsonStr)
            message = data["MessageData"]["members"]["message"]
            color = data["MessageData"]["members"]["color"]
            # ログを出力
            self.PrintLog("engine", message, color)
        except Exception as e:
            print(f"Error in __PrintRuntimeLog: {e}")