cmake_minimum_required(VERSION 3.20)

# 共通設定ファイルのインクルード
include("${CMAKE_SOURCE_DIR}/.cmake/common.cmake")
include("${CMAKE_SOURCE_DIR}/.cmake/windows_setting.cmake")

project("runtime" LANGUAGES CXX)

# C++の標準設定
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(WIN32)
	windows_setting()
endif()

# プリプロセッサの定義
add_definitions(-DUNICODE -D_UNICODE)

# 出力ディレクトリの設定
get_filename_component(PARENT_DIR ${CMAKE_SOURCE_DIR} DIRECTORY)
set(OUTPUT_DIR "${PARENT_DIR}/editor/Engine")

# Pythonの探索
find_package(Python REQUIRED COMPONENTS Interpreter Development)
message(STATUS "Including directory: ${Python_INCLUDE_DIRS}")

# ヘッダーファイルへのインクルードパスの追加
add_public_include_directory()

# サブディレクトリの追加
add_subdirectory("main")
add_subdirectory("core")
add_subdirectory("coreplugin")
add_subdirectory("platform")
add_subdirectory("editor")