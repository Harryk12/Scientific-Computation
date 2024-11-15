cmake_minimum_required( VERSION 3.20 )
project(Pascal VERSION 1.0)

message( "Using sources: abctuple.cpp" )
add_executable( abctuple )
target_sources( abctuple PRIVATE abctuple.cpp )

target_compile_features( abctuple PRIVATE cxx_std_20 )
install( TARGETS halfway DESTINATION . )
