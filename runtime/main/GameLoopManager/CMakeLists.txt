include("${CMAKE_SOURCE_DIR}/.cmake/common.cmake")
init_main_module_setting(GameLoopManager)
target_link_libraries(GameLoopManager "EventManager")