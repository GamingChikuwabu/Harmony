# Windows
if(WIN32)
  add_subdirectory(windows)
# macOS
elseif(APPLE)
  add_subdirectory(macos)
# Linux
elseif(UNIX AND NOT APPLE) # APPLE変数は、macOSとiOSの両方に対してtrueになります。
  add_subdirectory(linux)
# 特定のUNIXプラットフォーム
elseif(CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
  add_subdirectory(freebsd)
# Android
elseif(ANDROID)
  add_subdirectory(android)
# iOS
elseif(IOS)
  add_subdirectory(ios)
endif()