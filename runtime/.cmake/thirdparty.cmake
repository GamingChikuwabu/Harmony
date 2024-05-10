include(FetchContent)

# バージョンの指定
set(BDWGC_VERSION v8.2.6)
# パスの指定
set(BDWGC_GIT_PATH https://github.com/ivmai/bdwgc.git)

# libatomic_ops のクローン
FetchContent_Declare(
  libatomic_ops
  GIT_REPOSITORY https://github.com/ivmai/libatomic_ops.git
  GIT_TAG master
)

FetchContent_Declare(
  bdwgc
  GIT_REPOSITORY ${BDWGC_GIT_PATH}
  GIT_TAG ${BDWGC_VERSION} 
)

FetchContent_Declare(
  rapidjson
  GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
  GIT_TAG v1.1.0
)

FetchContent_GetProperties(libatomic_ops)
if(NOT libatomic_ops_POPULATED)
  FetchContent_Populate(libatomic_ops)
endif()

FetchContent_GetProperties(bdwgc)
if(NOT bdwgc_POPULATED)
  FetchContent_Populate(bdwgc)
  execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink
      ${libatomic_ops_SOURCE_DIR}
      ${bdwgc_SOURCE_DIR}/libatomic_ops
  )
  # bdwgc のビルドオプションを設定
  set(enable_cplusplus ON CACHE BOOL "Enable C++ support" FORCE)
  # DLLとしてビルドするためのオプションを設定
  set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libraries (DLLs)" FORCE)

  # bdwgc のディレクトリをプロジェクトに追加
  add_subdirectory(${bdwgc_SOURCE_DIR} ${bdwgc_BINARY_DIR})
endif()

FetchContent_GetProperties(rapidjson)
if(NOT rapidjson_POPULATED)
  FetchContent_Populate(rapidjson)
  
  # rapidjson のビルドオプションを設定
  set(RAPIDJSON_BUILD_DOC OFF CACHE BOOL "Disable doc building" FORCE)
  set(RAPIDJSON_BUILD_TESTS OFF CACHE BOOL "Disable tests" FORCE)

  add_subdirectory(${rapidjson_SOURCE_DIR} ${rapidjson_BINARY_DIR})
endif()
