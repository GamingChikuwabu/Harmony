from PySide6.QtCore import Qt,QDataStream,QIODevice,Signal
from PySide6.QtWidgets import QApplication, QMainWindow, QTreeView, QVBoxLayout, QWidget
from PySide6.QtGui import QStandardItem,QStandardItemModel,QDropEvent,QDrag,QContextMenuEvent
from Hierarchy.view.vGameObjectItem import vGameObjectItem
from Hierarchy.view.vSceneObjectItem import vSceneObjectItem
from Hierarchy.pSceneObject import pSceneObject
from Hierarchy.view.vCreateObjectContextMenu import vCreateObjectContextMenu
import json

class vHierarchyTree(QTreeView):
    # シグナルの定義
    becameTopSignal = Signal(str)
    removeTopSignal = Signal(str)
    context_menu_str = Signal(str,str)
    
    def __init__(self) -> None:
        super().__init__()
        # アイテムモデルの初期化
        self.ItemModel = QStandardItemModel()
        self.setModel(self.ItemModel)
        # ヘッダーを非表示に設定
        self.setHeaderHidden(True)
        # ドラッグ＆ドロップを有効化
        self.setDragEnabled(True)
        self.setAcceptDrops(True)
        self.setDragDropMode(QTreeView.InternalMove)

    # 名前から子アイテムを検索するメソッド
    def find_child_item_from_name(self, name)->QStandardItem:
        for row in range(self.ItemModel.rowCount()):
            item = self.ItemModel.item(row)
            if item.text() == name:
                return item
        return None
    
    # 名前からシーンを追加するメソッド
    def add_scene_from_name(self,name,parent_name):
        parentitem = self.find_child_item_from_name(parent_name)
        if parentitem is None:
            pSceneObject(self.ItemModel)
        else:
            pSceneObject(parentitem)

    # コンテキストメニューイベントのオーバーライド
    def contextMenuEvent(self, arg__1: QContextMenuEvent) -> None:
        context_menu = vCreateObjectContextMenu()
        action = context_menu.exec(arg__1.pos())
        index = self.indexAt(arg__1.pos())
        item = self.ItemModel.itemFromIndex(index)
        self.context_menu_str.emit(action.text(),item.text())
        return super().contextMenuEvent(arg__1)
    
    # マウスプレスイベントのオーバーライド
    def mousePressEvent(self, event):
        super().mousePressEvent(event)
        if event.button() == Qt.LeftButton:
            self.dragStartPosition = event.pos()

    # マウスムーブイベントのオーバーライド
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

    # ドロップイベントのオーバーライド
    def dropEvent(self, event: QDropEvent) -> None:
        # 親クラスのdropEventを呼び出す
        super().dropEvent(event)
        # ドラッグされたアイテムがvGameObjectItem形式のデータを持っているか確認
        if event.mimeData().hasFormat("application/vnd.myapp.vGameObjectItem.objectdata"):
           
            # ドラッグされたアイテムのオブジェクトデータを取得し、JSON形式からデコード
            objectdata_bytes = event.mimeData().data("application/vnd.myapp.vGameObjectItem.objectdata")
            objectdata_json = bytes(objectdata_bytes).decode()
            objectdata = json.loads(objectdata_json)
            # ドラッグされたアイテムのGUIDを取得
            guid_bytes = event.mimeData().data("application/vnd.myapp.vGameObjectItem.guid")
            guid = bytes(guid_bytes).decode()

            # 新しいvGameObjectItemを作成
            CopyItem = vGameObjectItem(objectdata,guid)
            # アイテムのコピーを行う
            self.ItemCopy(self.Dragitem,CopyItem)

            # ドロップされた位置のインデックスを取得
            index = self.indexAt(event.pos())
            # ドロップされた位置がトップレベルかどうかを判断し、シグナルを発行
            if index.parent() is None:
                self.becameTopSignal.emit(guid)
            else:
                self.removeTopSignal.emit(guid)

            # ドロップされた位置のアイテムを取得
            receiver = self.ItemModel.itemFromIndex(index)
            
            # ドロップされたアイテムがドラッグされたアイテムと異なり、かつ子孫でない場合
            if receiver != self.Dragitem and not self.isDescendantOf(receiver, self.Dragitem):
                # ドロップされたアイテムがvGameObjectItemのインスタンスである場合
                if isinstance(receiver, vGameObjectItem):
                    # ドロップされたアイテムにコピーされたアイテムを追加
                    receiver.appendRow(CopyItem)
                    
                    # ドラッグされたアイテムの親を取得し、親が存在する場合はその行を削除
                    parent = self.Dragitem.parent()
                    if parent is not None:
                        row = self.Dragitem.row()
                        parent.removeRow(row)
                    else:
                        # 親が存在しない場合は、アイテムモデルから直接行を削除
                        self.ItemModel.removeRow(self.Dragitem.row())
            else:
                # ドロップ操作を無視
                event.ignore()

    # 子孫かどうかを判断するメソッド
    def isDescendantOf(self, potentialDescendant, potentialAncestor):
        current = potentialDescendant
        while current is not None:
            if current == potentialAncestor:
                return True
            current = current.parent()
        return False
    
    # アイテムのコピーを行うメソッド
    def ItemCopy(self,Itemparent:vGameObjectItem,copyItemparent:vGameObjectItem):
        for i in  range(Itemparent.rowCount()):
            copychild = vGameObjectItem(Itemparent.child(i).objectdata,Itemparent.child(i).guid)
            copyItemparent.appendRow(copychild)
            self.ItemCopy(Itemparent.child(i),copychild)

    # ドラッグエンターイベントのオーバーライド
    def dragEnterEvent(self, event):
        super().dragEnterEvent(event)
        if event.mimeData().hasFormat("application/vnd.myapp.vGameObjectItem.objectdata"):
            event.accept()
        else:
            event.ignore()

    # ドラッグムーブイベントのオーバーライド
    def dragMoveEvent(self, event):
        super().dragMoveEvent(event)
        if event.mimeData().hasFormat("application/vnd.myapp.vGameObjectItem.objectdata"):
            event.accept()
        else:
            event.ignore()