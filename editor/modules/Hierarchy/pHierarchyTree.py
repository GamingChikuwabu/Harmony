from Hierarchy.view.vHierarchyTree import vHierarchyTree
from Hierarchy.model.mHierarchyTree import mHierarchyTree
from Hierarchy.pSceneObject import pSceneObject
import IPresenter
import os
import PathManager
import sys
import ModuleManager

#ヒエラルキービューのツリーのプレゼンター
@IPresenter.register("HierarchyTree")
class pHierarchyTree(IPresenter.IPresenter):
    def __init__(self) -> None:
        self.view = vHierarchyTree()#view
        self.model = mHierarchyTree()#model
        self.view.context_menu_str.connect(self.model.send_add_scene)

    def init_data(self):
        pass

    def init_UI(self):
        #TreeWidgetをコンテナオブジェクトに追加する
        hierarchy_window = ModuleManager.manager.get_module("Hierarchy")
        hierarchy_window.view.vlayout.addWidget(self.view)
        
    def Init_After_Runtime(self):
        super().Init_After_Runtime()