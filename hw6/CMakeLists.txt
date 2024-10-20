cmake_minimum_required( VERSION 3.20 )
project(perfectnum VERSION 1.0)

message( "Using sources: halfway.cpp" )
add_executable( perfectnum )
target_sources( perfectnum PRIVATE perfectnum.cpp )

target_compile_features( perfectnum PRIVATE cxx_std_17 )
install( TARGETS halfway DESTINATION . )
