include("${CMAKE_SOURCE_DIR}/.cmake/common.cmake")
init_editor_module_setting(HMModLevelEditor)
target_link_libraries(HMModLevelEditor HMModIPCManager HMModSceneManager)