class Metadata:
    def __init__(self, key: str, value):
        self.key = key
        self.value = value

class Property:
    def __init__(self,name,type) -> None:
        self.name = name
        self.type = type

class ClassConfig:
    def __init__(self):
        self.class_name = ""
        # クラスのプロパティ名とそのメタ情報の辞書
        self.class_properties = {}
        # クラスのメソッド名とそのメタ情報の辞書
        self.class_methods = {}
        # クラスのコンストラクタとそのメタ情報
        self.class_constructor = {"name": "", "metas": []}  # メタデータはリストで管理
        # クラスの所属する名前空間
        self.name_spase = []
    
    def get_name_space(self)->str:
        retstr = ""
        for namespace in self.name_spase:
            retstr += namespace 
            retstr += "::"
        return retstr[:-2]

    def add_property(self, prop:Property, meta: list):
        """プロパティを追加するメソッド。メタ情報はMetadataオブジェクトで指定。"""
        if prop not in self.class_properties:
            self.class_properties[prop] = []
        self.class_properties[prop].append(meta)

    def add_method(self, name, meta: list):
        """メソッドを追加するメソッド。メタ情報はMetadataオブジェクトで指定。"""
        if name not in self.class_methods:
            self.class_methods[name] = []
        self.class_methods[name].append(meta)

    def set_constructor(self, name, meta: list):
        """コンストラクタの情報を設定するメソッド。メタ情報はMetadataオブジェクトで指定。"""
        self.class_constructor["name"] = name
        self.class_constructor["metas"].append(meta)

    def add_namespace(self,name):
        self.name_spase.append(name)