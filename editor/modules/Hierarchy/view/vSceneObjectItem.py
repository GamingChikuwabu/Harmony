from PySide6.QtGui import QStandardItem,QIcon
from PySide6.QtCore import QMimeData,QByteArray,Qt
import json
import os
import PathManager

class vSceneObjectItem(QStandardItem):
    def __init__(self,name):
        super().__init__(name)
        self.setIcon(QIcon(os.path.join(PathManager.PathManager.ApplicationPath,"icon","scene.png")))
        self.setCheckState(Qt.Checked)

    def createMimeData(self):
        mimeData = QMimeData()
        objectdata_json = json.dumps(self.objectdata)
        objectdata_bytes = objectdata_json.encode()
        guid_bytes = str(self.guid).encode()
        mimeData.setData("application/vnd.myapp.vSceneObjectItem.objectdata", QByteArray(objectdata_bytes))
        mimeData.setData("application/vnd.myapp.vSceneObjectItem.guid", QByteArray(guid_bytes))
        return mimeData