cmake_minimum_required( VERSION 3.20 )
project(fizzbuzz_unix VERSION 1.0)

message( "Using sources: fizzbuzz_unix.cpp" )
add_executable( fizzbuzz_unix )
target_sources( fizzbuzz_unix PRIVATE fizzbuzz_unix.cpp )

target_compile_features( fizzbuzz_unix PRIVATE cxx_std_17 )
install( TARGETS fizzbuzz_unix DESTINATION . )
install( FILES script.sh DESTINATION . )
