macro(Build_Init targetname)
    # privateフォルダの中から.cppファイルを全て取得
    file(GLOB_RECURSE SOURCES_CPP "${CMAKE_CURRENT_SOURCE_DIR}/private/*.cpp")
    file(GLOB_RECURSE SOURCES_PRIVATE_H "${CMAKE_CURRENT_SOURCE_DIR}/private/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/private/*.hpp")
    file(GLOB_RECURSE SOURCES_PUBLIC_H "${CMAKE_CURRENT_SOURCE_DIR}/public/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/public/*.hpp")
    
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/public)
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/public/ DESTINATION include)

    if(SOURCES_CPP)  # 修正: 変数を展開しない
        message(STATUS "Found cpp files: ${SOURCES_CPP}")  # 修正: 追加のメッセージタイプ
        add_library(${targetname} SHARED ${SOURCES_CPP} ${SOURCES_PRIVATE_H} ${SOURCES_PUBLIC_H})
        
        string(TOUPPER ${targetname} target_upper)
        # Windows以外の場合は空の定義を使用
        if(NOT WIN32)
            set(EXPORT_DLL "")
            set(IMPORT_DLL "")
        else()
            # Windowsの場合は__declspecを設定
            set(EXPORT_DLL "__declspec(dllexport)")
            set(IMPORT_DLL "__declspec(dllimport)")
        endif()

        # ビルドするライブラリ自体にはEXPORT_DLLを使用
        target_compile_definitions(${targetname} PRIVATE ${target_upper}_API=${EXPORT_DLL})
        target_compile_definitions(${targetname} INTERFACE ${target_upper}_API=${IMPORT_DLL})
        message(STATUS "${target_upper}_API set to: ${EXPORT_DLL}")  # 修正: 追加のメッセージタイプ
    endif()
endmacro()