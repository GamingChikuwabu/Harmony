from clang.cindex import Config

def setup_libclang(lib_clang_path):
    """libclangの設定をする"""
    Config.set_library_file(lib_clang_path)
