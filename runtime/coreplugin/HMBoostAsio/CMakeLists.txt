include("${CMAKE_SOURCE_DIR}/.cmake/common.cmake")
init_coreplugin_module_setting(HMBoostAsio)
# ターゲットに対して_WIN32_WINNTを定義する
target_compile_definitions(HMBoostAsio PRIVATE -D_WIN32_WINNT=0x0601 -D_BOOST_NO_ANSI_APIS)
target_compile_definitions(HMBoostAsio PRIVATE ASIO_STANDALONE ASIO_NO_DEPRECATED)
#boost
target_include_directories(HMBoostAsio PRIVATE "${CMAKE_SOURCE_DIR}/thirdparty/boost/include")
target_link_directories(HMBoostAsio PRIVATE  "${CMAKE_SOURCE_DIR}/thirdparty/boost/lib/lib")