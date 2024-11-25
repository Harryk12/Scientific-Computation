cmake_minimum_required( VERSION 3.12 )
project( matvec VERSION 1.0 )

add_executable( matvec matvec.cpp )
target_compile_features( matvec PRIVATE cxx_std_23 )

find_package( Eigen3 REQUIRED  )
target_link_libraries( matvec PUBLIC Eigen3::Eigen )

install( TARGETS matvec DESTINATION . )
