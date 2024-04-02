include("${CMAKE_SOURCE_DIR}/.cmake/common.cmake")
init_main_module_setting(EventManager)
target_link_libraries(EventManager "UtilityCore" "Utility")