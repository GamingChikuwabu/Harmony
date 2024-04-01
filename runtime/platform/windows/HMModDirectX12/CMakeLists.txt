include("${CMAKE_SOURCE_DIR}/.cmake/common.cmake")
init_platform_module_setting(HMModDirectX12)
include("${CMAKE_SOURCE_DIR}/.cmake/thirdparty/directx12.cmake")
link_lib_DX12(HMModDirectX12)