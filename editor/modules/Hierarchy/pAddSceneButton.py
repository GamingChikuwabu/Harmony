from Hierarchy.view.vAddSceneButton import vAddSceneButton
from Hierarchy.view.vCreateObjectContextMenu import vCreateSceneContextMenu
from Hierarchy.model.mAddSceneButton import mAddSceneButton
from PySide6.QtCore import QPoint
import uuid
import os
import json

class pAddSceneButton:
    def __init__(self,layout) -> None:
        self.view = vAddSceneButton()
        layout.addWidget(self.view)
        self.model = mAddSceneButton()
        self.view.clicked.connect(self.print_menu)
    
    def print_menu(self,event):
        menu = vCreateSceneContextMenu()
        # ボタンのグローバル座標を取得
        button_global_pos = self.view.mapToGlobal(QPoint(0, 0))
        # ボタンのサイズを取得
        button_size = self.view.size()
        # メニューの表示位置を、ボタンの左下に調整
        menu_pos = button_global_pos + QPoint(0, button_size.height())
        action = menu.exec(menu_pos)
        if action and action.text() == "StaticBackground":
            self.create_new_scene_file()
            self.model.send_new_scene(3)
        elif action and action.text() == "UI":
            self.model.send_new_scene(0)
        elif action and action.text() == "Database":
            self.model.send_new_scene(1)

    #metaファイルと空のシーンファイルを作成する
    def create_new_scene_file(self,dir,name)->str:
        #metaファイルの生成
        meta_file_path = os.path.join(dir,name+".scene.meta")
        guid = uuid.uuid4()
        data = {
            "guid":str(guid)
        }
        with open(meta_file_path, 'w', encoding='utf-8') as f:
            json_str = json.dumps(data)
            f.write(json_str)
        #sceneファイルの生成
        scene_file_path = os.path.join(dir,name+".scene")
        with open(scene_file_path, 'w', encoding='utf-8') as f:
            pass
        return str(guid)