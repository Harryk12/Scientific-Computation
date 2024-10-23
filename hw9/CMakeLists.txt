cmake_minimum_required( VERSION 3.20 )
project(Pascal VERSION 1.0)

message( "Using sources: linkedlist.cpp" )
add_executable( linkedlist )
target_sources( linkedlist PRIVATE linkedlist.cpp )

target_compile_features( linkedlist PRIVATE cxx_std_17 )
install( TARGETS halfway DESTINATION . )
