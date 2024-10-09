cmake_minimum_required( VERSION 3.20 )
project(halfway VERSION 1.0)

message( "Using sources: halfway.cpp" )
add_executable( halfway )
target_sources( halfway PRIVATE halfway.cpp )

target_compile_features( halfway PRIVATE cxx_std_17 )
install( TARGETS halfway DESTINATION . )
