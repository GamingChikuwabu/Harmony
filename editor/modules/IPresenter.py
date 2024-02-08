from PySide6.QtCore import QSettings
import ModuleManager

# モジュールを登録するためのデコレータ
def register(name):
    def decorator(cls):
        ModuleManager.manager.register_module(name, cls)
        return cls
    return decorator

def menu_event(name):
    def decorator(func):
        if not hasattr(func, '_menu_items'):
            func._menu_items = []
        func._menu_items.append(name)
        return func
    return decorator


class IPresenter:
    #データの初期化関数
    def init_data(self):
        pass

    #UIの初期化関数
    def init_UI(self):
        pass

    def deserialize_UI(self,setting:QSettings):
        pass

    #RunTimeと接続された後の初期化処理
    def Init_After_Runtime(self):
        pass
    
    #終了処理
    def Terminate(self,setting:QSettings):
        pass