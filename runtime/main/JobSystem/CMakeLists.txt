include("${CMAKE_SOURCE_DIR}/.cmake/common.cmake")
init_main_module_setting(JobSystem)
target_link_libraries(JobSystem "Utility" "UtilityCore")