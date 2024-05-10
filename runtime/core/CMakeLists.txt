include(${CMAKE_SOURCE_DIR}/.cmake/corebuildsetting.cmake)
Build_Init(core)
include(${CMAKE_SOURCE_DIR}/.cmake/thirdparty.cmake)
target_include_directories("core" PUBLIC ${bdwgc_SOURCE_DIR}/include )
target_include_directories("core" PUBLIC ${libatomic_ops_SOURCE_DIR}/src)
target_include_directories("core" PRIVATE ${rapidjson_SOURCE_DIR}/include)
target_link_libraries(core PUBLIC gc gccpp gctba cord)
install(TARGETS core
        RUNTIME DESTINATION bin  # for Windows
        LIBRARY DESTINATION lib  # for Unix-like systems
        ARCHIVE DESTINATION lib) # for static libraries