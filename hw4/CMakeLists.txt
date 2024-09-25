cmake_minimum_required( VERSION 3.20 )
project( newton-lambda VERSION 1.0 )

message( "Using sources: newton.cpp" )
add_executable( newton-lambda )
target_sources( newton-lambda PRIVATE newton-lambda.cpp )

target_compile_features( newton-lambda PRIVATE cxx_std_17 )
install( TARGETS newton-lambda DESTINATION . )

