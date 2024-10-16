cmake_minimum_required( VERSION 3.20 )
project(Pascal VERSION 1.0)

message( "Using sources: Pascal.cpp" )
add_executable( Pascal )
target_sources( Pascal PRIVATE Pascal.cpp )

target_compile_features( Pascal PRIVATE cxx_std_17 )
install( TARGETS halfway DESTINATION . )
