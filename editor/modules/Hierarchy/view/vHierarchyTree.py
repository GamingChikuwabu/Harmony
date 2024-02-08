from PySide6.QtCore import Qt,QDataStream,QIODevice,Signal
from PySide6.QtWidgets import QApplication, QMainWindow, QTreeView, QVBoxLayout, QWidget
from PySide6.QtGui import QStandardItem,QStandardItemModel,QDropEvent,QDrag,QContextMenuEvent
from Hierarchy.view.vGameObjectItem import vGameObjectItem
from Hierarchy.view.vSceneObjectItem import vSceneObjectItem
from Hierarchy.pSceneObject import pSceneObject
from Hierarchy.view.vCreateObjectContextMenu import vCreateObjectContextMenu
import json

class vHierarchyTree(QTreeView):
    becameTopSignal = Signal(str)
    removeTopSignal = Signal(str)
    context_menu_str = Signal(str,str)
    def __init__(self) -> None:
        super().__init__()
        self.ItemModel = QStandardItemModel()
        self.setModel(self.ItemModel)
        self.setHeaderHidden(True)
        self.setDragEnabled(True)
        self.setAcceptDrops(True)
        self.setDragDropMode(QTreeView.InternalMove)

    def find_child_item_from_name(self, name)->QStandardItem:
        for row in range(self.ItemModel.rowCount()):
            item = self.ItemModel.item(row)
            if item.text() == name:
                return item
        return None
    
    def add_scene_from_name(self,name,parent_name):
        parentitem = self.find_child_item_from_name(parent_name)
        if parentitem is None:
            pSceneObject(self.ItemModel)
        else:
            pSceneObject(parentitem)

    def contextMenuEvent(self, arg__1: QContextMenuEvent) -> None:
        context_menu = vCreateObjectContextMenu()
        action = context_menu.exec(arg__1.pos())
        index = self.indexAt(arg__1.pos())
        item = self.ItemModel.itemFromIndex(index)
        self.context_menu_str.emit(action.text(),item.text())
        return super().contextMenuEvent(arg__1)
    
    def mousePressEvent(self, event):
        super().mousePressEvent(event)
        if event.button() == Qt.LeftButton:
            self.dragStartPosition = event.pos()

    def mouseMoveEvent(self, event):
        super().mouseMoveEvent(event)
        if not (event.buttons() & Qt.LeftButton):
            return
        if (event.pos() - self.dragStartPosition).manhattanLength() < QApplication.startDragDistance():
            return
        drag = QDrag(self)
        index = self.currentIndex()  
        if not index.isValid():
            return
        model = self.model()
        self.Dragitem = self.ItemModel.itemFromIndex(index) 
        if isinstance(self.Dragitem , vGameObjectItem):
            mimeData = self.Dragitem.createMimeData()  
            drag.setMimeData(mimeData)
            drag.exec_(Qt.MoveAction | Qt.CopyAction)

    def dropEvent(self, event: QDropEvent) -> None:
        super().dropEvent(event)
        if event.mimeData().hasFormat("application/vnd.myapp.vGameObjectItem.objectdata"):
           
            objectdata_bytes = event.mimeData().data("application/vnd.myapp.vGameObjectItem.objectdata")
            objectdata_json = bytes(objectdata_bytes).decode()
            objectdata = json.loads(objectdata_json)
            guid_bytes = event.mimeData().data("application/vnd.myapp.vGameObjectItem.guid")
            guid = bytes(guid_bytes).decode()

        
            CopyItem = vGameObjectItem(objectdata,guid)
            self.ItemCopy(self.Dragitem,CopyItem)

           
            index = self.indexAt(event.pos())
            if index.parent() is None:
                self.becameTopSignal.emit(guid)
            else:
                self.removeTopSignal.emit(guid)

            receiver = self.ItemModel.itemFromIndex(index)
            
            if receiver != self.Dragitem and not self.isDescendantOf(receiver, self.Dragitem):
                if isinstance(receiver, vGameObjectItem):
                    receiver.appendRow(CopyItem)
                    
                    parent = self.Dragitem.parent()
                    if parent is not None:
                        row = self.Dragitem.row()
                        parent.removeRow(row)
                    else:
                        self.ItemModel.removeRow(self.Dragitem.row())
            else:
                
                event.ignore()

    def isDescendantOf(self, potentialDescendant, potentialAncestor):
        current = potentialDescendant
        while current is not None:
            if current == potentialAncestor:
                return True
            current = current.parent()
        return False
    
    def ItemCopy(self,Itemparent:vGameObjectItem,copyItemparent:vGameObjectItem):
        for i in  range(Itemparent.rowCount()):
            copychild = vGameObjectItem(Itemparent.child(i).objectdata,Itemparent.child(i).guid)
            copyItemparent.appendRow(copychild)
            self.ItemCopy(Itemparent.child(i),copychild)

    def dragEnterEvent(self, event):
        super().dragEnterEvent(event)
        if event.mimeData().hasFormat("application/vnd.myapp.vGameObjectItem.objectdata"):
            event.accept()
        else:
            event.ignore()

    def dragMoveEvent(self, event):
        super().dragMoveEvent(event)
        if event.mimeData().hasFormat("application/vnd.myapp.vGameObjectItem.objectdata"):
            event.accept()
        else:
            event.ignore()