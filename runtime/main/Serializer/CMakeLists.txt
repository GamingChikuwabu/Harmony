include("${CMAKE_SOURCE_DIR}/.cmake/common.cmake")
init_main_module_setting(Serializer)
target_link_libraries(Serializer "Utility" "Reflection")