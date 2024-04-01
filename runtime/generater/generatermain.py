import sys
from clang.cindex import CursorKind, Index, TranslationUnit,SourceRange
from config import setup_libclang
import util
from class_config import ClassConfig
import os

def main():
    # libclangのパスとヘッダーファイルのパスを設定
    lib_clang_path = sys.argv[1]
    header_file_path = sys.argv[2]
    output_file_path = sys.argv[3]
    filename = sys.argv[4]

    name_h = filename + ".generate.h"
    name_cpp  = filename + ".gen.cpp"
    output_file_path_h = os.path.join(sys.argv[3],name_h)
    output_file_path_cpp = os.path.join(sys.argv[3],name_cpp)

    setup_libclang(lib_clang_path)
    index = Index.create()
    translation_unit = index.parse(header_file_path, args=["-x", "c++"])
    class_config = ClassConfig()

    util.build_class_configuration_with_tokens(translation_unit,class_config)

    # ファイルを開いてテキストを書き込む
    if class_config.isVaild:
        #ヘッダを生成
        with open(output_file_path_h, 'w',encoding= "utf-8") as file:
            file.write('#pragma once\n')
            file.write(f'#define HM_GENARATE_BODY_{class_config.class_name} \\\n')
            file.write("private:\\\n")
            file.write(f"friend struct G_Class_Declaration_Field_{class_config.class_name};\\\n")
            file.write(f"static HARMONY::Class* G_GetClassData{class_config.class_name}();\\\n")
            file.write(f"public:\\\n")
            file.write(f"static inline HARMONY::Class* StaticGetClass()\\\n")
            file.write("{\\\n")
            file.write(f"return G_GetClassData{class_config.class_name}();\\\n")
            file.write("}\\\n")
            file.write(f"inline virtual HARMONY::Class* GetClass()\\\n")
            file.write("{\\\n")
            file.write(f"return {class_config.class_name}::StaticGetClass();\\\n")
            file.write("}\n")
            file.write("#undef _GENARATED\n")
            file.write(f"#define _GENARATED  HM_GENARATE_BODY_{class_config.class_name}")

        #cppを生成
        with open(output_file_path_cpp, 'w',encoding= "utf-8") as file:
            file.write(f'#include"{filename}.h"\n')
            file.write(f'#include"Class/ClassBuilder.h"\n')
            file.write(f'#include"Class/deteil/ClassData.h"\n')
            file.write(f'#include"Macro/GenerateMacro.h"\n')
            file.write(f'static void G_AUTO_REGISTER_FUNCTION_{class_config.class_name}()\n')
            file.write('{\n')
            fullname = ""
            for name in class_config.name_spase:
                fullname += name + "::"
            file.write(f'    HARMONY::ClassBuilder::Registration(TEXT("{class_config.class_name}"), &{fullname}{class_config.class_name}::StaticGetClass);\n')
            file.write('}\n')

            file.write(f'struct AUTO_REGISTER_STRUCTURE_{class_config.class_name}\n')
            file.write('{\n')
            file.write(f'   AUTO_REGISTER_STRUCTURE_{class_config.class_name}()\n')
            file.write('    {\n')
            file.write(f'       G_AUTO_REGISTER_FUNCTION_{class_config.class_name}();\n')
            file.write('    }\n')
            file.write('};\n')
            file.write(f'struct AUTO_REGISTER_STRUCTURE_{class_config.class_name} ARS')
            file.write("={};\n")
            #名前空間の始まり
            for name in class_config.name_spase:
                file.write(f"namespace {name}")
                file.write('{\n')
            
            #メンバ情報の記述
            file.write(f"   struct G_Class_Declaration_Field_{class_config.class_name}\n")
            file.write('    {\n')
            file.write(f'       const static inline HMArray<Property*> _propertyField = \n')
            file.write('        {\n')
            for prop in class_config.class_properties.keys():
                if prop.type == "int32_t" or prop.type == "int" or prop.type == "uint32_t":
                    file.write(f'           HM_ADD_PROPERTY_INT32({class_config.class_name},{prop.name}),\n')
                elif prop.type == "int64_t" or prop.type == "long long" or prop.type == "uint64_t":
                    file.write(f'           HM_ADD_PROPERTY_INT64({class_config.class_name},{prop.name}),\n')
                elif prop.type == "float":
                    file.write(f'           HM_ADD_PROPERTY_FLOAT({class_config.class_name},{prop.name}),\n')
                elif prop.type == "HMString":
                    file.write(f'           HM_ADD_PROPERTY_STRING({class_config.class_name},{prop.name}),\n')
                elif prop.type == "bool":
                    file.write(f'           HM_ADD_PROPERTY_BOOL({class_config.class_name},{prop.name}),\n')
                elif prop.type == "HMArray":
                    file.write(f'           HM_ADD_PROPERTY_ARRAY({class_config.class_name},{prop.name}),\n')

            file.write('        };\n')
            file.write('    };\n')

            file.write(f"   inline Class* {class_config.class_name}::G_GetClassData{class_config.class_name}()\n")
            file.write('    {\n')
            if "" != class_config.base_class_name and "gc" != class_config.base_class_name:
                file.write(f'       HM_CLASS_CREATE({class_config.class_name},&{class_config.base_class_name}::StaticGetClass)\n')
            else:
                file.write(f'       HM_CLASS_CREATE({class_config.class_name},nullptr)\n')
            file.write('return _class;\n')
            file.write('\n')
            file.write('    }\n')

            #名前空間の終了
            for name in class_config.name_spase:
                file.write('}\n')

            print(f"==============================generate completion {class_config.class_name}===========================================")

if __name__ == "__main__":
    main()
    