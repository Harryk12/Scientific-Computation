cmake_minimum_required( VERSION 3.20 )
project(simulations)

set(sim1_source
  sim1.cpp
)
set(sim2_source
  sim2.cpp
)
set(sim3_source
  sim3.cpp
)
set(sim4_source
  sim4.cpp
)
set(sim5_source
  sim5.cpp
)
set(sim6_source
  sim6.cpp
)

add_executable( sim1 ${sim1_source} )
add_executable( sim2 ${sim2_source} )
add_executable( sim3 ${sim3_source} )
add_executable( sim4 ${sim4_source} )
add_executable( sim5 ${sim5_source} )
add_executable( sim6 ${sim6_source} )

set_target_properties(sim1 sim2 sim3 sim4 sim5 sim6 PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
