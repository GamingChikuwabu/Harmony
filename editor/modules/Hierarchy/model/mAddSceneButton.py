import IPCManager
import uuid
import IPCManager
import struct

class mAddSceneButton:
    def __init__(self) -> None:
        self.IPC = IPCManager.IPCManager()
        pass

    def send_new_scene(self,typeid,guid = None,name = None):
        #新規シーンの作成
        if name is None:
            name = str("newscene")
        scene_name = name.encode('utf-8')
        scene_name_length = len(scene_name)


        if guid is None:
            guid = str(uuid.uuid4())
        scene_guid = guid.encode('utf-8')
        scene_guid_length = len(scene_guid)

        datasize = scene_name_length + 4 + scene_guid_length + 4 + 4
        
        # フォーマット: シーン名の長さ、シーン名、GUIDの長さ、GUID、追加の整数データ
        packed_data = struct.pack('<I{}sI{}sI'.format(scene_guid_length,scene_name_length), 
                                scene_guid_length, scene_guid,
                                scene_name_length, scene_name, 
                                typeid)
        # データを送信
        self.IPC.SendData(datasize, IPCManager.IPCManager().commandlist["CreateSceneObject"], packed_data)


    def send_add_scene(self):
        parent = "root_parent"#rootのシーン
        self.IPC.SendData()