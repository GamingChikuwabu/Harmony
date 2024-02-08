#Windowsアプリケーションにする
if(WIN32)
    add_executable(runtimexe "private/main.cpp" "public/main.h")
else()
    add_executable(runtimexe "private/main.cpp" "public/main.h")
endif()

target_link_libraries(runtimexe PRIVATE "ModuleManager" "GameLoopManager" "LogManager" "TypeManager")
set_target_properties(runtimexe PROPERTIES
        
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}/main"
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}/lib/main"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}/main"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}/lib/main"
        RUNTIME_OUTPUT_DIRECTORY_DEVELOP "${OUTPUT_DIR}/main"
        ARCHIVE_OUTPUT_DIRECTORY_DEVELOP "${OUTPUT_DIR}/lib/main"
    )