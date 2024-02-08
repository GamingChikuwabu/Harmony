include("${CMAKE_SOURCE_DIR}/.cmake/common.cmake")
init_platform_module_setting(HMModDirectX12)
target_include_directories(HMModDirectX12 PRIVATE "${CMAKE_SOURCE_DIR}/thirdparty/platform/windows/DirectXTex/include")
target_link_libraries(HMModDirectX12 "${CMAKE_SOURCE_DIR}/thirdparty/platform/windows/DirectXTex/lib/debug/DirectXTex.lib")