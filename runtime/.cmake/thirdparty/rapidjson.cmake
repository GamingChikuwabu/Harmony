function(link_lib target_name)
    target_include_directories(${target_name} PRIVATE "${CMAKE_SOURCE_DIR}/thiedparty/include/rapidjson")
endfunction()