from PySide6.QtCore import QSettings,QByteArray
from PySide6.QtWidgets import QMainWindow

class vMainWindow(QMainWindow):
    def __init__(self) -> None:
        super().__init__()
        self.setWindowTitle("Kaleidoscope")
        self.setGeometry(100, 100, 1280, 720)
        self.setDockOptions(QMainWindow.AllowNestedDocks | QMainWindow.AllowTabbedDocks)
        self.setObjectName("Kaleidoscope")
        self.setDockNestingEnabled(True)