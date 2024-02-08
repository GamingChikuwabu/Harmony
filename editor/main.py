from PySide6.QtWidgets import QApplication,QToolButton,QMainWindow
from PySide6.QtCore import QSettings
import qdarktheme
import os
import sys


#エントリーポイント
if __name__ == '__main__':
    #パス設定
    if getattr(sys, 'frozen', False):
        application_path = os.path.dirname(sys.executable)
    elif __file__:
        application_path = os.path.dirname(__file__)

    # フォルダをPythonの検索パスに追加
    manager_path = os.path.join(application_path,"manager")
    modules_path = os.path.join(application_path,"modules")
    sys.path.insert(0, manager_path)
    sys.path.insert(0, modules_path)

    #pathmanagerにパスを登録
    from PathManager import PathManager
    PathManager.WorkSpaceDir = sys.argv[6]
    PathManager.ApplicationPath = application_path

    #アプリケーションの初期化開始
    app = QApplication(sys.argv)
    settings = QSettings("MyCompany", "HARMONY")
    #見た目の変更
    qdarktheme.enable_hi_dpi()
    qdarktheme.setup_theme()

    #moduleの読み込み
    import ModuleManager
    ModuleManager.load_modules_from_directory(os.path.join(PathManager.ApplicationPath,"modules"))
    ModuleManager.manager.init_data()
    ModuleManager.manager.init_UI()
    ModuleManager.manager.deserialize_UI(settings)
    from IPCManager import IPCManager
    #subprocessの起動
    manager = IPCManager()
    #manager.start_runtime([os.path.join(PathManager.ApplicationPath,"Engine","main","runtimexe.exe")])
    manager.modeltcp.connectsignal.connect(ModuleManager.manager.Init_After_Runtime)
    app.exec()
    manager.shutdown()
    ModuleManager.manager.Terminate(settings)
    sys.exit(0)