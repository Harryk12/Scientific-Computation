cmake_minimum_required( VERSION 3.20 )
project(Pascal VERSION 1.0)

message( "Using sources: newton-complex.cpp" )
add_executable( newton-complex )
target_sources( newton-complex PRIVATE newton-complex.cpp )

target_compile_features( newton-complex PRIVATE cxx_std_17 )
install( TARGETS halfway DESTINATION . )
