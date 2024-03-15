# 現在のプラットフォームを検出
if(WIN32)
  # Windowsの場合
  message(STATUS "Configuring for Windows...")
  
  # MSVCを使用する場合の設定例
  set(CMAKE_C_COMPILER "cl.exe")
  set(CMAKE_CXX_COMPILER "cl.exe")

elseif(APPLE)
  # macOSの場合
  message(STATUS "Configuring for macOS...")
  
  # Clangを使用する場合の設定例
  set(CMAKE_C_COMPILER "/usr/bin/clang")
  set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

elseif(UNIX AND NOT APPLE)
  # Linuxの場合
  message(STATUS "Configuring for Linux...")
  
  # GCCを使用する場合の設定例
  set(CMAKE_C_COMPILER "/usr/bin/gcc")
  set(CMAKE_CXX_COMPILER "/usr/bin/g++")
  
else()
  # サポートされていないプラットフォーム
  message(FATAL_ERROR "Unsupported platform.")
endif()