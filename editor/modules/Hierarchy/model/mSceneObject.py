import IPCManager
from PySide6.QtCore import QObject,Signal
import struct

class mSceneObject(QObject):
    new_scene_object_signal_str_str =Signal(str,str)
    def __init__(self) -> None:
        super().__init__()
        self.IPC = IPCManager.IPCManager()
        self.IPC.RegisterReceveDataCallBack(self.IPC.commandlist["AddedScene"],self.add_new_scene_from_runtime)

    def add_new_scene_from_runtime(self, data):
        # 受信したシーンデータを処理
        rdata = struct.unpack('<32s64s64sI', data)
        name_data = rdata[0].decode('utf-8', 'ignore').rstrip('\x00')
        parent_guid = rdata[2].decode('utf-8', 'ignore').rstrip('\x00')
        # 受信データに基づいて信号を発行
        self.new_scene_object_signal_str_str.emit(name_data, parent_guid)