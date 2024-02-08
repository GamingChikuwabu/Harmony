include("${CMAKE_SOURCE_DIR}/.cmake/common.cmake")
init_editor_module_setting(HMModConsole)
target_link_libraries(HMModConsole HMModIPCManager)