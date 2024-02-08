import os
import importlib.util
import IPresenter
from PySide6.QtCore import QSettings

class ModuleManager:
    def __init__(self):
        self.modules = {}
        
    def init_data(self):
        #データの初期化
        for i in self.modules.values():
            if isinstance(i,IPresenter.IPresenter):
                i.init_data()

    def init_UI(self):
        #データの初期化
        for i in self.modules.values():
            if isinstance(i,IPresenter.IPresenter):
                i.init_UI()
    
    def deserialize_UI(self,setting:QSettings):
        #データの初期化
        for i in self.modules.values():
            if isinstance(i,IPresenter.IPresenter):
                i.deserialize_UI(setting)
    
    def Init_After_Runtime(self):
        for i in self.modules.values():
            if isinstance(i,IPresenter.IPresenter):
                i.Init_After_Runtime()

    def Terminate(self,setting:QSettings):
        for i in self.modules.values():
            if isinstance(i,IPresenter.IPresenter):
                i.Terminate(setting)

    def register_module(self, name, cls):
        self.modules[name] = cls()
        print(f"Module {name} loaded.")   

    def get_module(self, name):
        return self.modules.get(name)
    
def load_modules_from_directory(directory):
    for filename in os.listdir(directory):
        if filename.endswith('.py') and not filename.startswith('__'):
            module_name = filename[:-3]  # 拡張子.pyを除去
            module_path = os.path.join(directory, filename)
            spec = importlib.util.spec_from_file_location(module_name, module_path)
            module = importlib.util.module_from_spec(spec)
            spec.loader.exec_module(module)
             
            
# モジュールマネージャーインスタンスの作成
manager = ModuleManager()