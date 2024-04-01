include("${CMAKE_SOURCE_DIR}/.cmake/common.cmake")
init_main_module_setting(LogManager)
target_link_libraries(LogManager "EventManager" "Utility")