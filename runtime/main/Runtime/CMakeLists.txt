#Windowsアプリケーションにする
if(WIN32)
    add_executable(runtimexe WIN32 "private/main.cpp" "public/main.h")
else()
    add_executable(runtimexe "private/main.cpp" "public/main.h")
endif()

target_link_libraries(runtimexe "ModuleManager" "GameLoopManager" "LogManager" "Utility" "Reflection" "Object")
set_target_properties(runtimexe PROPERTIES
        
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}/main"
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}/lib/main"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}/main"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}/lib/main"
        RUNTIME_OUTPUT_DIRECTORY_DEVELOP "${OUTPUT_DIR}/main"
        ARCHIVE_OUTPUT_DIRECTORY_DEVELOP "${OUTPUT_DIR}/lib/main"
    )

include("${CMAKE_SOURCE_DIR}/.cmake/thirdparty/bdwgc.cmake")
LINK_LIB_GC(runtimexe)