import IPresenter
from PySide6.QtGui import QStandardItem
from Hierarchy.view.vGameObjectItem import vGameObjectItem
from Hierarchy.model.mGameObject import mGameObject

class pGameObject(IPresenter.IPresenter):
    def __init__(self,parent:QStandardItem) -> None:
        self.model = mGameObject()
        self.view = vGameObjectItem()
        parent.appendRow(self.view)
    