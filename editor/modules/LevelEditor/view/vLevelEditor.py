from PySide6.QtCore import QThread, Signal,Qt,QTimer
from PySide6.QtWidgets import QMainWindow,QFrame,QDockWidget,QHBoxLayout

class vLevelEditor(QDockWidget):
    resizeSignal = Signal()
    def __init__(self, title):
        super().__init__(title)
        self.hlayout = QHBoxLayout()
        self.frame = QFrame(self)
        self.setWidget(self.frame)
        self.setObjectName(title)
        self.setFeatures(QDockWidget.DockWidgetMovable | QDockWidget.DockWidgetFloatable)
        self.resizeTimer = QTimer(self)
        self.resizeTimer.setSingleShot(True)
        self.resizeTimer.timeout.connect(self.onResizeTimerTimeout)
        self.resizeTimer.setInterval(100)  # 500ミリ秒後にタイムアウト

    def resizeEvent(self, event):
        # リサイズイベントが発生するたびにタイマーをリスタート
        self.resizeTimer.start()
        super().resizeEvent(event)

    def onResizeTimerTimeout(self):
        # タイマーがタイムアウトしたらリサイズ終了とみなす
        self.resizeSignal.emit()