from PySide6.QtWidgets import QPushButton,QMenu

class vCreateObjectContextMenu(QMenu):
    def __init__(self):
        super().__init__()
        dynamic_scene_menu = QMenu("DynamicScene")
        dynamic_scene_menu.addAction("StaticBackground")

        static_scene_menu = QMenu("StaticScene")
        static_scene_menu.addAction("UI")
        static_scene_menu.addAction("Database")

        self.addMenu(dynamic_scene_menu)
        self.addMenu(static_scene_menu)

        self.triggered.connect(self.actionClicked)

    def actionClicked(self, action):
        # クリックされたアクションを処理
        print(f"クリックされたアクション: {action.text()}")