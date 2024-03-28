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

    #proptype == "bool"or
     #   proptype == "int32_t"or
      #  proptype == "int64_t"or
       # proptype == "uint32_t"or
        #proptype == "uint64_t"or
        #proptype == "HMString"or
        #proptype == "HMArray"or
        #proptype == "HMUnorderedMap"or
        #proptype == "float"or
        #proptype == "double"):

    # ファイルを開いてテキストを書き込む

    #ヘッダを生成
    with open(output_file_path_h, 'w',encoding= "utf-8") as file:
        file.write('#pragma once\n')
        file.write(f'#define HM_GENARATE_BODY_{class_config.class_name}\\\n')
        file.write("private:\\\n")
        file.write(f"friend struct G_Class_Declaration_Field_{class_config.class_name};\\\n")
        file.write(f"static HARMONY::Class* G_GetClassData{class_config.class_name}();\\\n")
        file.write(f"public:\\\n")
        file.write(f"static inline HARMONY::Class* GetClass()\\\n")
        file.write("{\\\n")
        file.write(f"return G_GetClassData{class_config.class_name}();\\\n")
        file.write("}\\\n")
        file.write("#undef _GENARATED\n")
        file.write(f"#define _GENARATED  HM_GENARATE_BODY_{class_config.class_name}")

    #cppを生成
    with open(output_file_path_cpp, 'w',encoding= "utf-8") as file:
        file.write(f'#include"{filename}.h"\n')
        file.write(f'#include"Class/ClassBuilder.h"\n')
        file.write(f'#include"Class/deteil/ClassData.h"\n')
        file.write(f'static void G_AUTO_REGISTER_FUNCTION_{class_config.class_name}()\n')
        file.write('{\n')
        fullname = ""
        for name in class_config.name_spase:
            fullname += name + "::"
        file.write(f'   HARMONY::ClassBuilder::Registration(TEXT("HMObject"), &{fullname}{class_config.class_name}::GetClass);\n')
        file.write('}\n')

        file.write(f'struct AUTO_REGISTER_STRUCTURE_{class_config.class_name}\n')
        file.write('{\n')
        file.write(f'   AUTO_REGISTER_STRUCTURE_{class_config.class_name}()\n')
        file.write('    {\n')
        file.write(f'       static void G_AUTO_REGISTER_FUNCTION_{class_config.class_name}();\n')
        file.write('    }\n')
        file.write('}\n')
        file.write(f'struct AUTO_REGISTER_STRUCTURE_{class_config.class_name} ARS;\n')
        #名前空間の始まり
        for name in class_config.name_spase:
            file.write(f"namespace {name}")
            file.write('{\n')
        
        #メンバ情報の記述
        file.write(f"   struct G_Class_Declaration_Field_{class_config.class_name}\n")
        file.write('    {\n')
        file.write(f'       const static inline HMArray<Property*> _propertyField = \n')
        file.write('        {\n')
        #ここにプロパティを記述
        file.write('        }\n')
        file.write('    }\n')

        file.write(f"   inline Class* HMObject::G_GetClassData{class_config.class_name}()\n")
        file.write('    {\n')
        file.write(r'       static Class* _class = new (GC_NEW(Class)) Class(new (GC_NEW(ClassData)) ClassData(TEXT("HMObject"), sizeof(HMObject), G_Class_Declaration_Field_HMObject::_propertyField)	);return _class;')
        file.write('\n')
        file.write('    }\n')

        #名前空間の終了
        for name in class_config.name_spase:
            file.write('}\n')

if __name__ == "__main__":
    main()