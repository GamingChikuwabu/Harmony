macro(lib_setting targetname)
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
    add_compile_definitions(_SILENCE_CXX20_CISO646_REMOVED_WARNING)
    message(${target_upper}_API)
    target_compile_definitions(${targetname} PRIVATE ${target_upper}_EXPORTS=1)
endmacro()

macro(defo_module_setting targetname)
     # ソースファイルを探す
    file(GLOB KS_MODULE_MANAGER_SOURCES "private/*.cpp" "public/*.h" "generate/*.cpp" "generate/*.h")
    # ターゲットの追加
    add_library(${targetname} SHARED ${KS_MODULE_MANAGER_SOURCES})
    message(${KS_MODULE_MANAGER_SOURCES})
    #dllやsoのセッティング
    lib_setting(${targetname})
    #自分のprivateディレクトリのインクルードパスを通す
    target_include_directories(${targetname} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/${targetname}/private")
    #Utirytyともつなぐ
    target_include_directories(${targetname} PRIVATE "${CMAKE_SOURCE_DIR}/utility")
    #Eigenのパス
    target_include_directories(${targetname} PRIVATE "${CMAKE_SOURCE_DIR}/thirdparty/Eigen")
    target_include_directories(${targetname} PRIVATE "${CMAKE_SOURCE_DIR}/thirdparty/platform/windows/rttr/include")
    #GCのパスを通す
    target_include_directories(${targetname} PRIVATE "${CMAKE_SOURCE_DIR}/thirdparty/platform/windows/bdwgc/include")
    target_link_directories(${targetname} PRIVATE  "${CMAKE_SOURCE_DIR}/thirdparty/platform/windows/bdwgc/lib/debug")
    target_link_libraries(${targetname} "${CMAKE_SOURCE_DIR}/thirdparty/platform/windows/bdwgc/lib/debug/gc.lib")
    target_link_libraries(${targetname} "${CMAKE_SOURCE_DIR}/thirdparty/platform/windows/bdwgc/lib/debug/gccpp.lib")
    target_link_libraries(${targetname} "${CMAKE_SOURCE_DIR}/thirdparty/platform/windows/bdwgc/lib/debug/gctba.lib")
    target_link_libraries(${targetname} "${CMAKE_SOURCE_DIR}/thirdparty/platform/windows/rttr/lib/Debug/rttr_core_d.lib")
    #CUSTOM_HEADER_GENERATER(${targetname})
endmacro()

macro(init_main_module_setting targetname)
    defo_module_setting(${targetname})
    set_target_properties(${targetname} PROPERTIES
        
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}/main"
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}/lib/main"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}/main"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}/lib/main"
        RUNTIME_OUTPUT_DIRECTORY_DEVELOP "${OUTPUT_DIR}/main"
        ARCHIVE_OUTPUT_DIRECTORY_DEVELOP "${OUTPUT_DIR}/lib/main"
    )
endmacro()

macro(init_core_module_setting targetname)
    defo_module_setting(${targetname})
   
    set_target_properties(${targetname} PROPERTIES
        
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}/core"
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}/lib/core"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}/core"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}/lib/core"
        RUNTIME_OUTPUT_DIRECTORY_DEVELOP "${OUTPUT_DIR}/core"
        ARCHIVE_OUTPUT_DIRECTORY_DEVELOP "${OUTPUT_DIR}/lib/core"
    )
    
    target_link_libraries(${targetname} ModuleManager EventManager GameLoopManager JobSystem)
endmacro()

macro(init_coreplugin_module_setting targetname)
    defo_module_setting(${targetname})
    
    set_target_properties(${targetname} PROPERTIES
        
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}/coreplugin"
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}/lib/coreplugin"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}/coreplugin"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}/lib/coreplugin"
        RUNTIME_OUTPUT_DIRECTORY_DEVELOP "${OUTPUT_DIR}/coreplugin"
        ARCHIVE_OUTPUT_DIRECTORY_DEVELOP "${OUTPUT_DIR}/lib/coreplugin"
    )
    
    target_link_libraries(${targetname} ModuleManager EventManager GameLoopManager JobSystem)
endmacro()

macro(init_platform_module_setting targetname)
    defo_module_setting(${targetname})
    # プラットフォーム名を設定
    if(WIN32)
        set(platformname "windows")
    elseif(APPLE)
        set(platformname "macos")
    elseif(UNIX AND NOT APPLE)
        set(platformname "linux")
    elseif(CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
        set(platformname "freebsd")
    elseif(ANDROID)
        set(platformname "android")
    elseif(IOS)
        set(platformname "ios")
    else()
        set(platformname "unknown")
    endif()
    # ターゲットプロパティを設定
    set_target_properties(${targetname} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}/platform/${platformname}"
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}/lib/platform/${platformname}"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}/platform/${platformname}"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}/lib/platform/${platformname}"
        RUNTIME_OUTPUT_DIRECTORY_DEVELOP "${OUTPUT_DIR}/platform/${platformname}"
        ARCHIVE_OUTPUT_DIRECTORY_DEVELOP "${OUTPUT_DIR}/lib/platform/${platformname}"
    )
    #ModuleManagerとリンクする
    target_link_libraries(${targetname} ModuleManager EventManager GameLoopManager JobSystem)
endmacro()

macro(init_editor_module_setting targetname)
    defo_module_setting(${targetname})
    # DLLの出力拡張子を.pydに設定
    set_target_properties(${targetname} PROPERTIES
        
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}/editor"
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}/lib/editor"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}/editor"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}/lib/editor"
        RUNTIME_OUTPUT_DIRECTORY_DEVELOP "${OUTPUT_DIR}/editor"
        ARCHIVE_OUTPUT_DIRECTORY_DEVELOP "${OUTPUT_DIR}/lib/editor"
    )
    #ModuleManagerとリンクする
    target_link_libraries(${targetname} ModuleManager EventManager GameLoopManager JobSystem)
endmacro()

macro(init_project_module_setting targetname)
    defo_module_setting(${targetname})
    # DLLの出力拡張子を.pydに設定
    set_target_properties(${targetname} PROPERTIES
        
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}/editor"
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}/lib/editor"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}/editor"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}/lib/editor"
        RUNTIME_OUTPUT_DIRECTORY_DEVELOP "${OUTPUT_DIR}/editor"
        ARCHIVE_OUTPUT_DIRECTORY_DEVELOP "${OUTPUT_DIR}/lib/editor"
    )
    #ModuleManagerとリンクする
    target_link_libraries(${targetname} ModuleManager EventManager GameLoopManager JobSystem)
endmacro()

function(add_sub_modules)
    # サブディレクトリを含むディレクトリを指定
    set(SUBDIRS_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
    # サブディレクトリを探索してリストに追加
    file(GLOB SUBDIRS LIST_DIRECTORIES true RELATIVE "${SUBDIRS_DIR}" "${SUBDIRS_DIR}/*")
    # ディレクトリのみをフィルタリング
    foreach(SUBDIR ${SUBDIRS})
        if(IS_DIRECTORY "${SUBDIRS_DIR}/${SUBDIR}")
            add_subdirectory("${SUBDIRS_DIR}/${SUBDIR}")
        endif()
    endforeach()
endfunction()

function(add_public_include_directory )
    file(GLOB_RECURSE ALL_FILES "${CMAKE_SOURCE_DIR}/*/*/public/*")
    set(DIR_PATHS "")
    foreach(FILE_PATH ${ALL_FILES})
        get_filename_component(DIR_PATH ${FILE_PATH} DIRECTORY)
        list(APPEND DIR_PATHS ${DIR_PATH})
    endforeach()

    list(REMOVE_DUPLICATES DIR_PATHS)

    foreach(DIR_PATH ${DIR_PATHS})
        include_directories(${DIR_PATH})
        message(STATUS "Including directory: ${DIR_PATH}")
    endforeach()
    file(GLOB_RECURSE ALL_FILES "${CMAKE_SOURCE_DIR}/*/*/*/public/*")
    set(DIR_PATHS "")
    foreach(FILE_PATH ${ALL_FILES})
        get_filename_component(DIR_PATH ${FILE_PATH} DIRECTORY)
        list(APPEND DIR_PATHS ${DIR_PATH})
    endforeach()

    list(REMOVE_DUPLICATES DIR_PATHS)

    foreach(DIR_PATH ${DIR_PATHS})
        include_directories(${DIR_PATH})
        message(STATUS "Including directory: ${DIR_PATH}")
    endforeach()
endfunction()

macro(custom_header_generater targetname)
    #libclangのパス
    set(LIB_CLANG_PATH ${CMAKE_SOURCE_DIR}/.cmake/libclang.dll)
    #pythonfileのパス
    set(HEADER_GENERATER_PATH ${CMAKE_SOURCE_DIR}/.cmake/header_generater.py)
    #.hファイルを探す
    file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/**/*.h")
    # ファイルのリストを出力する
    foreach(HEADER_FILE ${HEADER_FILES})
        get_filename_component(HEADER_NAME ${HEADER_FILE} NAME)
        message(STATUS "Found header file: ${HEADER_NAME}")
        add_custom_command(
            TARGET ${targetname}
            PRE_LINK
            COMMAND python3 ${HEADER_GENERATER_PATH} ${LIB_CLANG_PATH} ${HEADER_FILE} ${CMAKE_SOURCE_DIR}/generate/"${HEADER_NAME}generate.h"
            COMMENT "Generating custom header file"
        )
    endforeach()
endmacro()