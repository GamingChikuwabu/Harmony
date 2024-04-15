from PySide6.QtCore import QSettings,Qt,QByteArray
import IPresenter
import ModuleManager

@IPresenter.register("IPCSetting")
class IPCSetting(IPresenter.IPresenter):
    def __init__(self) -> None:
        pass

    @IPresenter.menu_event("edit/IPCEvent")
    def Setting(self):
        pass

    def init_UI(self):
        ModuleManager.manager.modules