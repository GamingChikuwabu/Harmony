from clang.cindex import CursorKind, Index, TokenKind, Config, TranslationUnit,Cursor
import sys

def find_class_node(cursor:Cursor, class_name):
    try:
        if cursor.kind == CursorKind.CLASS_DECL and cursor.spelling == class_name:
            return cursor
        for child in cursor.get_children():
            result = find_class_node(child, class_name)
            if result:
                return result
    except ValueError as e:
        print(f"ValueError: {e}. このノードはスキップされます。")
    return None

def find_class_by_token(translation_unit: TranslationUnit):
    """HMCLASSトークンを探してクラス名を取得する関数"""
    tokens = list(translation_unit.get_tokens(extent=translation_unit.cursor.extent))
    for i, token in enumerate(tokens):
        if token.spelling == 'HMCLASS':
            class_name = tokens[i + 4].spelling
            print(f"クラス名: {class_name}")
            return class_name
    return None

def find_class_property_by_AST(translation_unit: TranslationUnit, class_name: str):
    """ASTを走査してクラスのフィールドを探す"""
    class_node = find_class_node(translation_unit.cursor, class_name)
    if class_node:
        print(f"クラス '{class_name}' が見つかりました: {class_node.location}")
        tokens = list(translation_unit.get_tokens(extent=class_node.extent))
        for i, token in enumerate(tokens):
            if token.spelling == 'HMPROPERTY':
                class_name = tokens[i + 4].spelling
                print(f"変数名: {class_name}")
                return class_name
    else:
        print(f"クラス '{class_name}' は見つかりませんでした")

def main():
    # libclangのパスを設定
    lib_clang_path = sys.argv[1]    
    Config.set_library_file(lib_clang_path)
    header_file_path = sys.argv[2]
    index = Index.create()
    translation_unit = index.parse(header_file_path, args=["-x", "c++"])

    # クラス名を取得
    class_name = find_class_by_token(translation_unit)
    if class_name:
        find_class_property_by_AST(translation_unit, class_name)

if __name__ == "__main__":
    main()