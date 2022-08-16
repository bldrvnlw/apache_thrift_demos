cmake_minimum_required(VERSION 3.17)

project(ThriftTutorial VERSION 1.0
                  DESCRIPTION "Apache thrift tutorial"
                  LANGUAGES CXX)

add_subdirectory(gen-cpp)

message("srct: ${thrift_IF_src}")

add_executable(thrift_server ./server/server.cpp ${thrift_IF_src})
target_compile_features(thrift_server PRIVATE cxx_std_17)
target_include_directories(thrift_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../thrift_0_16/include C:/.conan/2412be/1/include)
target_compile_features(thrift_server PUBLIC cxx_std_11)
target_link_libraries(thrift_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../thrift_0_16/lib/thriftmd.lib)

add_executable(thrift_client ./client/client.cpp ${thrift_IF_src})
target_compile_features(thrift_client PRIVATE cxx_std_17)
target_include_directories(thrift_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../thrift_0_16/include C:/.conan/2412be/1/include)
target_compile_features(thrift_client PUBLIC cxx_std_11)
target_link_libraries(thrift_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../thrift_0_16/lib/thriftmd.lib)