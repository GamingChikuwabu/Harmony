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
    target_compile_definitions(${targetname} PRIVATE NOMINMAX)

    add_compile_definitions(_SILENCE_CXX20_CISO646_REMOVED_WARNING)
    message(${target_upper}_API)
    target_compile_definitions(${targetname} PRIVATE ${target_upper}_EXPORTS=1)

endmacro()

macro(lib_path_setting targetname)
    include("${CMAKE_SOURCE_DIR}/.cmake/thirdparty/rapidjson.cmake")
    link_lib(${targetname})
    include("${CMAKE_SOURCE_DIR}/.cmake/thirdparty/bdwgc.cmake")
    LINK_LIB_GC(${targetname})
endmacro()

macro(genarate_hedder_dir_setting targetname)
    

endmacro()

macro(defo_module_setting targetname)
     # ソースファイルを探す
    file(GLOB KS_MODULE_MANAGER_SOURCES "private/*.cpp" "public/*.h" "generate/*.cpp")
    # ターゲットの追加
    add_library(${targetname} SHARED ${KS_MODULE_MANAGER_SOURCES})
    lib_setting(${targetname})
    message(${KS_MODULE_MANAGER_SOURCES})
    #dllやsoのセッティング
    #自分のprivateディレクトリのインクルードパスを通す
    target_include_directories(${targetname} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/private")
    target_include_directories(${targetname} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/generate")
    
    lib_path_setting(${targetname})
    #custom_header_generator(${targetname})
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
    
    target_link_libraries(${targetname} ModuleManager EventManager GameLoopManager JobSystem Utility)
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
    
    target_link_libraries(${targetname} ModuleManager EventManager GameLoopManager JobSystem Utility)
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
    target_link_libraries(${targetname} ModuleManager EventManager GameLoopManager JobSystem Utility)
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
    target_link_libraries(${targetname} ModuleManager EventManager GameLoopManager JobSystem Utility)
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
    target_link_libraries(${targetname} ModuleManager EventManager GameLoopManager JobSystem Utility)
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

macro(custom_header_generator targetname)
    # libclangのパス
    set(LIB_CLANG_PATH ${CMAKE_SOURCE_DIR}/.cmake/libclang.dll)
    # generatemain.exeのパス
    set(GENERATE_MAIN_PATH ${CMAKE_SOURCE_DIR}/.cmake/generate.exe)
    # .hファイルを探す
    file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/**/*.h")

    # カスタムターゲット名
    set(custom_target_name "${targetname}_header_generator")

    # カスタムターゲットを追加
    add_custom_target(${custom_target_name} ALL)

    # ファイルのリストを出力し、各ファイルに対してカスタムコマンドを追加
    foreach(HEADER_FILE ${HEADER_FILES})
        get_filename_component(HEADER_NAME ${HEADER_FILE} NAME_WE)
        message(STATUS "Found header file: ${HEADER_NAME}")
        
        # カスタムコマンドをカスタムターゲットに追加
        add_custom_command(
            TARGET ${custom_target_name}
            COMMAND ${GENERATE_MAIN_PATH} ${LIB_CLANG_PATH} ${HEADER_FILE} ${CMAKE_SOURCE_DIR}/generate/"${HEADER_NAME}.generate.inc"
            COMMENT "Generating custom header file for ${HEADER_NAME}"
        )
    endforeach()

    # メインのターゲットがこのカスタムターゲットに依存するように設定
    add_dependencies(${targetname} ${custom_target_name})
endmacro()