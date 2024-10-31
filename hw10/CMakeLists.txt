cmake_minimum_required( VERSION 3.20 )
project( zeroclasstest VERSION 1.0 )
#project( require VERSION 1.0 )

message( "Using sources: zeroclasstest.cpp zeroclasslib" )
add_executable( zeroclasstest )
target_sources( zeroclasstest PRIVATE zeroclasstest.cpp zeroclassimp.cpp zeroclasslib.hpp )

##
## Extra packages: catch2
##
find_package( PkgConfig REQUIRED )
pkg_check_modules( CATCH2 REQUIRED catch2-with-main )
target_include_directories(
	zeroclasstest PUBLIC
	${CATCH2_INCLUDE_DIRS}
	)
target_link_directories(
	zeroclasstest PUBLIC
	${CATCH2_LIBRARY_DIRS}
	)
target_link_libraries(
	zeroclasstest PUBLIC
	${CATCH2_LIBRARIES}
	)

set_target_properties(
	zeroclasstest PROPERTIES
	BUILD_RPATH   "${CATCH2_LIBRARY_DIRS}"
	INSTALL_RPATH "${CATCH2_LIBRARY_DIRS}"
    )

install( TARGETS zeroclasstest DESTINATION . )
