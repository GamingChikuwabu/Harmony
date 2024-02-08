from PySide6.QtCore import QSettings,Qt,QByteArray
from PySide6.QtWidgets import QVBoxLayout
import IPresenter
import ModuleManager
from Hierarchy.view.vHierarchy import vHierarchy
from Hierarchy.model.mHierarchy import mHierarchy
from Hierarchy.pHierarchyTree import pHierarchyTree
from IPCManager import IPCManager
from Hierarchy.pSceneObject import pSceneObject
import os
import PathManager
import sys
import json

@IPresenter.register("Hierarchy")
class pHierarchy(IPresenter.IPresenter):
    def __init__(self) -> None:
        super().__init__()
        self.model = mHierarchy()
        self.view = vHierarchy("Hierarchy")
        self.IPC = IPCManager()
        
    def init_data(self):
        return super().init_data()
    
    def init_UI(self):
        mainwindow = ModuleManager.manager.get_module("MainWindow")
        mainwindow.mainwindow.addDockWidget(Qt.LeftDockWidgetArea,self.view)
        return super().init_UI()
    
    def Init_After_Runtime(self):
        return super().Init_After_Runtime()
    
    def deserialize_UI(self, setting: QSettings):
        return super().deserialize_UI(setting)
    
    def Terminate(self, setting: QSettings):
        return super().Terminate(setting)
    
    