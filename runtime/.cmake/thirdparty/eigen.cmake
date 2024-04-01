function(link_lib_Eigen target_name)
    target_include_directories(${target_name} PRIVATE "${CMAKE_SOURCE_DIR}/thiedparty/include/Eigen")
endfunction()