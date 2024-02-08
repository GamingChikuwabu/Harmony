from PySide6.QtCore import QSettings,Qt,QByteArray
import IPresenter
import ModuleManager
from Inspector.view.vInspector import vInspector


@IPresenter.register("Inspector")
class pInspector(IPresenter.IPresenter):
    def __init__(self) -> None:
        super().__init__()
    
    def init_data(self):
        return super().init_data()
    
    def init_UI(self):
        self.inspectorwindow = vInspector("Inspector")
        mainwindow = ModuleManager.manager.get_module("MainWindow")
        mainwindow.mainwindow.addDockWidget(Qt.LeftDockWidgetArea,self.inspectorwindow)
        return super().init_UI()
    
    def Init_After_Runtime(self):
        return super().Init_After_Runtime()
    
    def deserialize_UI(self, setting: QSettings):
        return super().deserialize_UI(setting)
    
    def Terminate(self, setting: QSettings):
        return super().Terminate(setting)