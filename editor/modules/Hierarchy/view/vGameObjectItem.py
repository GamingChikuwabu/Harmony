from PySide6.QtGui import QStandardItem,QIcon
from PySide6.QtCore import QMimeData,QByteArray
import json

class vGameObjectItem(QStandardItem):
    def __init__(self,name):
        super().__init__(name)

    def createMimeData(self):
        mimeData = QMimeData()
        objectdata_json = json.dumps(self.objectdata)
        objectdata_bytes = objectdata_json.encode()
        guid_bytes = str(self.guid).encode()
        mimeData.setData("application/vnd.myapp.vGameObjectItem.objectdata", QByteArray(objectdata_bytes))
        mimeData.setData("application/vnd.myapp.vGameObjectItem.guid", QByteArray(guid_bytes))
        return mimeData