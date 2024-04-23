import uuid
import json
import os
import PathManager
import xml.etree.ElementTree as ET
import sys
import IPCManager
import struct
from PySide6.QtCore import Signal,QObject

class mHierarchyTree(QObject):
    # 新しいシーンオブジェクトの信号（シーン名、親シーン名）
    new_scene_object_signal_str_str = Signal(str, str)

    def __init__(self):
        super().__init__()
        # IPCManagerのインスタンスを生成し、コールバックを登録
        self.IPC = IPCManager.IPCManager()

    def Load_last_open_scene_guid(self)->str:
        project_path = os.path.join(PathManager.PathManager.WorkSpaceDir,"ProjectsRoot",sys.argv[5],"project","config","sceneroot.json") 
        #前回開いたrootシーンのファイルがあるかの確認
        if os.path.exists(project_path):
            with open(project_path, 'r', encoding='utf-8') as f:
                data = json.load(f)
                self.now_scene_guid = data["guid"]
                return data["guid"]
        else:
            return None

    def create_scene_root_file(self, guid):
        # シーンルートファイルを作成
        file_data = {
            "guid": guid
        }
        project_path = os.path.join(PathManager.PathManager.WorkSpaceDir, "ProjectsRoot", "Sample", "project", "config", "sceneroot.json")
        with open(project_path, 'w', encoding='utf-8') as f:
            json_str = json.dumps(file_data)
            f.write(json_str)

    def load_scene_from_xml(self, guid: str):
        # XMLファイルからシーンを読み込む
        path = self.GetfilepathfromMeta(guid)
        try:
            tree = ET.parse(path)
        except:
            return None

        root = tree.getroot()
        subscene_guids_items = root.findall('.//_subSceneGuids/item')
        subscene_guids_list = [item.text for item in subscene_guids_items if item.text]

        scene_data = {
            "_sceneName": root.find('.//_sceneName').text,
            "_sceneGuid": root.find('.//_sceneGuid').text,
            "_sceneType": int(root.find('.//_sceneType').text),
            "_subSceneGuids": subscene_guids_list,
            "_subSceneGuids_count": int(root.find('.//_subSceneGuids/count').text)
        }
        return scene_data

    def GetfilepathfromMeta(self, uuid) -> str:
        # UUIDに基づいてメタデータのファイルパスを取得
        directory = os.path.join(PathManager.PathManager.WorkSpaceDir, 'ProjectsRoot', sys.argv[5])
        for dirpath, dirnames, filenames in os.walk(directory):
            for filename in filenames:
                if filename.endswith('.meta'):
                    full_path = os.path.join(dirpath, filename)
                    with open(full_path, 'r', encoding='utf-8') as f:
                        data = json.load(f)
                        if uuid == data['guid']:
                            return full_path[:-5]
        return None

    def create_new_scene_file(self, dir, name,typeid) -> str:
        # 新しいシーンファイルとメタファイルを作成
        guid = str(uuid.uuid4())
        meta_file_path = os.path.join(dir, name + ".scene.meta")
        scene_file_path = os.path.join(dir, name + ".scene")

        with open(meta_file_path, 'w', encoding='utf-8') as f:
            json.dump({"guid": guid,"type":typeid}, f)

        open(scene_file_path, 'w').close()
        return guid

    def send_add_scene(self, scene_type_name, parent_scene_name):
        # シーンを追加するためのデータを送信
        packed_data = struct.pack('<I32s', 3, parent_scene_name.encode("utf-8"))
        self.IPC.SendData(36, IPCManager.IPCManager().commandlist["AddScene"], packed_data)

    def send_new_scene(self, typeid, guid=None, name=None):
        # 新しいシーンを作成するためのデータを送信
        if name is None:
            name = "newscene"
        scene_name = name.encode('utf-8')
        scene_guid = (guid or str(uuid.uuid4())).encode('utf-8')

        packed_data = struct.pack('<32s64s64sI', scene_name, scene_guid, "".encode('utf-8'), typeid)
        self.IPC.SendData(32 + 64 + 64 + 4, IPCManager.IPCManager().commandlist["CreateSceneObject"], packed_data)