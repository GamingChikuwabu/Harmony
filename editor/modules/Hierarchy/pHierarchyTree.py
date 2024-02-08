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
        self.root_guid = None
        self.root_scenedata = None
        self.first_time_flg = False

    def init_data(self):
        #データの初期化
        #前回開いたシーンのGuidを取得
        self.root_guid = self.model.Load_last_open_scene_guid()
        if self.root_guid == None:#取得できないまたは初回起動時
            self.first_time_flg = True#初回起動のフラグを立てる
            #シーン名がdefaultの空のシーンファイルを作成する
            self.root_guid = self.model.create_new_scene_file(os.path.join(PathManager.PathManager.WorkSpaceDir,"ProjectsRoot",sys.argv[5],"assets","scene"),"default",4)
            #今起動しているシーンファイルを保存するjsonファイルを作成する
            self.model.create_scene_root_file(self.root_guid)
        #Rootのシーンデータを作成する
        self.root_scenedata = self.model.load_scene_from_xml(self.root_guid)#初回起動時はNoneが返る

    def init_UI(self):
        #TreeWidgetをコンテナオブジェクトに追加する
        hierarchy_window = ModuleManager.manager.get_module("Hierarchy")
        hierarchy_window.view.vlayout.addWidget(self.view)
        if self.root_scenedata is not None:
            scene_object = ModuleManager.manager.get_module("SceneObject")
            if isinstance(scene_object,pSceneObject):
                #Treeを形成する
                scene_object.add_scene_object(self.root_scenedata.get("_sceneName"),"root")#RootSceneを作成する
                self.__init_scene_object_tree(self.root_scenedata.get("_sceneName"),self.root_scenedata,scene_object)

    def Init_After_Runtime(self):
        if self.first_time_flg:
            self.model.send_new_scene(typeid=3,guid=self.root_guid,name="default")
            super().Init_After_Runtime()
    
    def __init_scene_object_tree(self,parent_name,data,scene_presenter:pSceneObject):
        for child_guid in data["_subSceneGuids"]:
            child_data = self.model.load_scene_from_xml(child_guid)
            scene_presenter.add_scene_object(child_data.get("_sceneName"),parent_name)
            self.__init_scene_object_tree(child_data.get("_sceneName"),child_data,scene_presenter)