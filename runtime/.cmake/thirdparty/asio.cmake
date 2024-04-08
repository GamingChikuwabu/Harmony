function(link_lib_Asio target_name)
    target_include_directories(${target_name} PUBLIC "${CMAKE_SOURCE_DIR}/thirdparty/include/asio")
endfunction()