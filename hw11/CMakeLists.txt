cmake_minimum_required( VERSION 3.20 )
project(Pascal VERSION 1.0)

message( "Using sources: newton-root.cpp" )
add_executable( newton-root )
target_sources( newton-root PRIVATE newton-root.cpp )

target_compile_features( newton-root PRIVATE cxx_std_17 )
install( TARGETS newton-root DESTINATION . )
