# ���݂̃v���b�g�t�H�[�������o
if(WIN32)
  # Windows�̏ꍇ
  message(STATUS "Configuring for Windows...")
  
  # MSVC���g�p����ꍇ�̐ݒ��
  set(CMAKE_C_COMPILER "cl.exe")
  set(CMAKE_CXX_COMPILER "cl.exe")

elseif(APPLE)
  # macOS�̏ꍇ
  message(STATUS "Configuring for macOS...")
  
  # Clang���g�p����ꍇ�̐ݒ��
  set(CMAKE_C_COMPILER "/usr/bin/clang")
  set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

elseif(UNIX AND NOT APPLE)
  # Linux�̏ꍇ
  message(STATUS "Configuring for Linux...")
  
  # GCC���g�p����ꍇ�̐ݒ��
  set(CMAKE_C_COMPILER "/usr/bin/gcc")
  set(CMAKE_CXX_COMPILER "/usr/bin/g++")
  
else()
  # �T�|�[�g����Ă��Ȃ��v���b�g�t�H�[��
  message(FATAL_ERROR "Unsupported platform.")
endif()