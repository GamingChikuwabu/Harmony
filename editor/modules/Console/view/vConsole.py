from PySide6.QtCore import QThread, Signal,Qt
from PySide6.QtWidgets import QMainWindow,QFrame,QDockWidget,QTabWidget,QTextEdit
from PySide6.QtGui import QTextCursor, QTextCharFormat, QColor

class vConsole(QDockWidget):
    def __init__(self, title):
        super().__init__(title)
        self.setFeatures(QDockWidget.DockWidgetMovable | QDockWidget.DockWidgetFloatable)
        self.setObjectName(title)
        self.tabWidget = QTabWidget(self)
        self.engineLog = QTextEdit()
        self.editorLog = QTextEdit()
        self.debugLog = QTextEdit()
        self.tabWidget.addTab(self.engineLog, "エンジンログ")
        self.tabWidget.addTab(self.editorLog, "エディターログ")
        self.tabWidget.addTab(self.debugLog, "デバッグログ")
        self.setWidget(self.tabWidget)
        
        self.engineLog.setReadOnly(True)
        self.editorLog.setReadOnly(True)
        self.debugLog.setReadOnly(True)
        
        self.engineLog.setVerticalScrollBarPolicy(Qt.ScrollBarAlwaysOn)
        self.editorLog.setVerticalScrollBarPolicy(Qt.ScrollBarAlwaysOn)
        self.debugLog.setVerticalScrollBarPolicy(Qt.ScrollBarAlwaysOn)
        
    def addLog(self, logType, message, color):
        
        if logType == "engine":
            text_edit = self.engineLog
        elif logType == "editor":
            text_edit = self.editorLog
        elif logType == "debug":
            text_edit = self.debugLog
        else:
            return  # 無効なログタイプの場合は何もしない

        # テキストのフォーマットを設定
        format = QTextCharFormat()
        format.setForeground(QColor(color))

        # メッセージを追加する
        text_edit.moveCursor(QTextCursor.End)
        cursor = text_edit.textCursor()
        cursor.setCharFormat(format)
        cursor.insertText(message + "\n")
        text_edit.moveCursor(QTextCursor.End)