add_executable(runtime WIN32 "main.cpp" "main.h")
install(TARGETS runtime DESTINATION bin)
target_link_libraries(runtime PRIVATE core)
target_include_directories(runtime PRIVATE ${CMAKE_SOURCE_DIR}/core/public)