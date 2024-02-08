include("${CMAKE_SOURCE_DIR}/.cmake/common.cmake")
init_editor_module_setting(HMModHierarchy)
target_link_libraries(HMModHierarchy HMModIPCManager HMModSceneManager)