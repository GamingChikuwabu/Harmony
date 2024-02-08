from PySide6.QtCore import QThread, Signal,Qt
from PySide6.QtWidgets import QMainWindow,QFrame,QDockWidget,QTabWidget,QTextEdit,QWidget,QHBoxLayout
from PySide6.QtGui import QTextCursor, QTextCharFormat, QColor

class vAssetsBrowser(QDockWidget):
    def __init__(self,title):
        super().__init__(title)
        self.setFeatures(QDockWidget.DockWidgetMovable | QDockWidget.DockWidgetFloatable)
        self.setObjectName(title)
        container = QWidget(self)
        boxlayout = QHBoxLayout(container)
        self.setLayout(boxlayout)
        container.setLayout(boxlayout)
        self.setWidget(container)