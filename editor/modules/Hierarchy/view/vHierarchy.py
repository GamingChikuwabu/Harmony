from PySide6.QtCore import QThread, Signal
from PySide6.QtWidgets import QDockWidget,QWidget,QVBoxLayout

class vHierarchy(QDockWidget):
    def __init__(self, title):
        super().__init__(title)
        self.setFeatures(QDockWidget.DockWidgetMovable | QDockWidget.DockWidgetFloatable)
        self.setObjectName(title)
        self.vlayout = QVBoxLayout()
        self.contenawidget = QWidget(self)
        self.setWidget(self.contenawidget)
        self.contenawidget.setLayout(self.vlayout)