include("${CMAKE_SOURCE_DIR}/.cmake/common.cmake")
init_main_module_setting(Utility)
target_link_libraries(Utility "Reflection" "UtilityCore")