from PySide6.QtCore import QThread, Signal,Qt
from PySide6.QtWidgets import QMainWindow,QFrame,QDockWidget,QWidget,QVBoxLayout,QTreeWidget,QTreeWidgetItem
class vInspector(QDockWidget):
    def __init__(self, title):
        super().__init__(title)
        self.setFeatures(QDockWidget.DockWidgetMovable | QDockWidget.DockWidgetFloatable)
        self.setObjectName(title)
        self.contener = QWidget(self)
        self.vlayout = QVBoxLayout(self.contener)
        self.vlayout.setAlignment(Qt.AlignTop)  # ウィジェットを上端に揃える
        self.contener.setLayout(self.vlayout)
        self.currentWidget = None
        self.setWidget(self.contener)