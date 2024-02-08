import IPresenter
from PySide6.QtGui import QStandardItem,QStandardItemModel
from Hierarchy.model.mSceneObject import mSceneObject
from Hierarchy.view.vSceneObjectItem import vSceneObjectItem

import ModuleManager

@IPresenter.register("SceneObject")
class pSceneObject(IPresenter.IPresenter):
    def __init__(self) -> None:
        self.model = mSceneObject()
        self.model.new_scene_object_signal_str_str.connect(self.add_scene_object)
        self.scene_object_dict = {}
    
    def init_data(self):
        return super().init_data()
    
    def init_UI(self):
        tree_item = ModuleManager.manager.get_module("HierarchyTree")
        from Hierarchy.pHierarchyTree import pHierarchyTree
        if isinstance(tree_item,pHierarchyTree):
            self.tree_root = tree_item.view.ItemModel
        return super().init_UI()
    
    #シーンオブジェクトを追加する関数
    def add_scene_object(self,scene_name,parent_name)->vSceneObjectItem:
        self.scene_object_dict[scene_name] = vSceneObjectItem(scene_name)
        if parent_name == "root":#親がrootの場合
            self.tree_root.appendRow(self.scene_object_dict[scene_name])
        else:
            self.scene_object_dict[parent_name].appendRow(self.scene_object_dict[scene_name])
        return self.scene_object_dict[scene_name]