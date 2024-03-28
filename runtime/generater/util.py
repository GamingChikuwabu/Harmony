from class_config import Metadata,ClassConfig,Property
from clang.cindex import CursorKind, Index, TranslationUnit,SourceRange

def find_namespace(cursor, namespace_name):
    """
    指定された名前空間を探す関数。

    Args:
        cursor (Cursor): 検索を開始するカーソル（通常はトランスレーションユニットのルート）。
        namespace_name (str): 探す名前空間の名前。

    Returns:
        Cursor: 見つかった名前空間のカーソル。見つからない場合はNone。
    """
    for c in cursor.get_children():
        # 名前空間のカーソルを探す
        if c.kind == CursorKind.NAMESPACE and c.spelling == namespace_name:
            return c
        # 再帰的に子カーソルも検索
        else:
            result = find_namespace(c, namespace_name)
            if result:
                return result
    return None

def register_class_name(index:int,tokens:list,class_config:ClassConfig):
    if "_API" in tokens[index+1].spelling:#dllの宣言が入っている場合
        class_name = tokens[index+2].spelling
        print(f"クラス名: {class_name}")
        class_config.class_name = class_name
    else:
        #前方宣言ではないことを調べる
        if ";" != tokens[index+2].spelling and ">" != tokens[index+2].spelling:
            class_name = tokens[index+1].spelling
            print(f"クラス名: {class_name}")
            class_config.class_name = class_name

def register_class_property(index:int,tokens:list,class_config:ClassConfig):
    #Metadataの収集
    meta_data = []
    meta_data_index = 0
    while tokens[index + meta_data_index].spelling != ")":
        if tokens[index + meta_data_index].spelling == "COMMENT":
            meta_data.append(Metadata("COMMENT",tokens[index + meta_data_index + 2].spelling))#2の理由はCOMMENT:”コメントです”になっている場合meta_data_indexはCOMMENTのことを指しているので2進めている
        meta_data_index += 1
    #Property情報の取得
    while tokens[index + meta_data_index].spelling != ";" and tokens[index + meta_data_index].spelling != "=":
        meta_data_index += 1
    name = tokens[index + meta_data_index - 1].spelling
    proptype = tokens[index + meta_data_index - 2].spelling
    pro = Property(name,proptype)
    class_config.add_property(pro,meta_data)

def register_namespace(index:int,tokens:list,class_config:ClassConfig):
    if tokens[index + 2].spelling == "{":
        class_config.add_namespace(tokens[index + 1].spelling)

def build_class_configuration_with_tokens(translation_unit,class_config:ClassConfig):
    tokens = list(translation_unit.get_tokens(extent=translation_unit.cursor.extent))
    for i, token in enumerate(tokens):
        if token.spelling == "class":
            register_class_name(i,tokens,class_config)
        elif token.spelling == "namespace":
            register_namespace(i,tokens,class_config)
        elif token.spelling == "HMPROPERTY":
            register_class_property(i,tokens,class_config)
        