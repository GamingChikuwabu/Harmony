include("${CMAKE_SOURCE_DIR}/.cmake/common.cmake")
include("${CMAKE_SOURCE_DIR}/.cmake/thirdparty/asio.cmake")
init_coreplugin_module_setting(HMBoostAsio)
# ターゲットに対して_WIN32_WINNTを定義する
target_compile_definitions(HMBoostAsio PRIVATE -D_WIN32_WINNT=0x0601 -D_BOOST_NO_ANSI_APIS)
target_compile_definitions(HMBoostAsio PRIVATE ASIO_STANDALONE ASIO_NO_DEPRECATED)
LINK_LIB_ASIO(HMBoostAsio)