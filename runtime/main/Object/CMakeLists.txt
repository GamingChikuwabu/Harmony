include("${CMAKE_SOURCE_DIR}/.cmake/common.cmake")
init_main_module_setting(Object)
target_link_libraries(Object "Utility" "Reflection")