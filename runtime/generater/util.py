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
        class_config.class_name = class_name
        if tokens[index+3].spelling == ":":
            class_config.base_class_name = tokens[index+5].spelling
    else:
        if class_config.class_name == "":
            #前方宣言ではないことを調べる
            if ";" != tokens[index+2].spelling and ">" != tokens[index+2].spelling:
                class_name = tokens[index+1].spelling
                class_config.class_name = class_name
            if tokens[index+2].spelling == ":":
                class_config.base_class_name = tokens[index+4].spelling

def register_class_property(index:int, tokens:list, class_config:ClassConfig):
    # Metadataの収集
    meta_data = []
    meta_data_index = 0
    tokens_length = len(tokens) # tokensリストの長さを取得
    while index + meta_data_index < tokens_length and tokens[index + meta_data_index].spelling != ")":
        if tokens[index + meta_data_index].spelling == "COMMENT":
            # COMMENTの後ろには少なくとも2つのトークンが必要なので、範囲チェックを追加
            if index + meta_data_index + 2 < tokens_length:
                meta_data.append(Metadata("COMMENT", tokens[index + meta_data_index + 2].spelling))
        meta_data_index += 1

    name = ""
    proptype = ""
    while index + meta_data_index < tokens_length:
        if tokens[index + meta_data_index].spelling == ";":#変数宣言の端まで来た
            if proptype == "":
                proptype = tokens[index + meta_data_index - 2].spelling
            name = tokens[index + meta_data_index - 1].spelling
            break
        elif  tokens[index + meta_data_index].spelling == "=":#変数を初期化している場合
            if proptype == "":
                proptype = tokens[index + meta_data_index - 2].spelling
            name = tokens[index + meta_data_index - 1].spelling
            break
        elif  tokens[index + meta_data_index].spelling == "<":#テンプレートを使用する型の場合
            proptype = tokens[index + meta_data_index - 1].spelling
        meta_data_index += 1
        if index + meta_data_index - 2 < index:
            print("ループの終了条件に達したが、有効なプロパティ名と型が見つからなかった")
            return
        
    pro = Property(name, proptype)
    class_config.add_property(pro, meta_data)

def register_namespace(index:int,tokens:list,class_config:ClassConfig):
    if tokens[index + 2].spelling == "{":
        class_config.add_namespace(tokens[index + 1].spelling)

def build_class_configuration_with_tokens(translation_unit,class_config:ClassConfig):
    tokens = list(translation_unit.get_tokens(extent=translation_unit.cursor.extent))
    for i, token in enumerate(tokens):
        if token.spelling == "HMCLASS" and tokens[i-1].spelling != "define":
            class_config.isVaild = True
        elif token.spelling == "class" or token.spelling == "struct":
            register_class_name(i,tokens,class_config)
        elif token.spelling == "namespace":
            register_namespace(i,tokens,class_config)
        elif token.spelling == "HMPROPERTY":
            register_class_property(i,tokens,class_config)