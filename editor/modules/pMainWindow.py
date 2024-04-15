from PySide6.QtCore import QSettings,QByteArray
from PySide6.QtGui import QAction,QIcon
from PySide6.QtWidgets import QMenuBar,QMenu
import IPresenter
import os
import PathManager
import ModuleManager
from MainWindow.view.vMainWindow import vMainWindow

@IPresenter.register("MainWindow")
class pMainWindow(IPresenter.IPresenter):
    def __init__(self) -> None:
        super().__init__()
        self.mainwindow = vMainWindow()
        self.menubar = QMenuBar(self.mainwindow)
        self.mainwindow.setMenuBar(self.menubar)
    
    def init_data(self):
        return super().init_data()
    
    def init_UI(self):
        self.mainwindow.setWindowIcon(QIcon(os.path.join(PathManager.PathManager.ApplicationPath,"icon","Logo.png")))
        func = self.find_menu_functions()
        for menu_path, callback in func.items():
            self.create_menu_item(menu_path, callback)
        self.mainwindow.showMaximized()
        return super().init_UI()
    
    def deserialize_UI(self, setting: QSettings):
        state = setting.value("windowState", QByteArray())
        if not state.isEmpty():
            self.mainwindow.restoreState(state)
        return super().deserialize_UI(setting)
    
    def Terminate(self, setting: QSettings):
        setting.setValue("windowState", self.mainwindow.saveState())
        return super().Terminate(setting)
    
    #menu_eventデコレータで登録したコールバック関数を探す
    def find_menu_functions(self):
        menu_functions = {}
        for module in ModuleManager.manager.modules.values():
            if isinstance(module, IPresenter.IPresenter):
                for attr_name in dir(module):
                    attr = getattr(module, attr_name)
                    if callable(attr) and hasattr(attr, '_menu_items'):
                        for menu_name in attr._menu_items:
                            menu_functions[menu_name] = attr
                            print(f"メニュー登録: {menu_name} -> {attr}")  # デバッグ出力
        return menu_functions
    
    def create_menu_item(self, menu_path, callback):
        menu_names = menu_path.split('/')
        current_menu = self.menubar

        for name in menu_names[:-1]:
            # 既存のメニューを検索または新しく作成
            found = False
            for action in current_menu.actions():
                if action.menu() and action.text() == name:
                    current_menu = action.menu()
                    found = True
                    break
            if not found:
                new_menu = QMenu(name, self.mainwindow)
                current_menu.addMenu(new_menu)
                current_menu = new_menu

        # アクションの作成と追加
        action = QAction(menu_names[-1], self.mainwindow)
        action.triggered.connect(callback)
        current_menu.addAction(action)