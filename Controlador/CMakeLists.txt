cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(controlador_plugin)

# Find Gazebo
find_package(gazebo REQUIRED)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})

# Find Boost
find_package(Boost REQUIRED COMPONENTS system)

# Set compile flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")

# Add the plugin library
add_library(controlador_plugin SHARED controlador_plugin.cpp)

# Link the libraries
target_link_libraries(controlador_plugin 
    ${GAZEBO_LIBRARIES}
    ${Boost_LIBRARIES}
)

# Set C++ standard
set_target_properties(controlador_plugin PROPERTIES 
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

# Install the plugin
install(TARGETS controlador_plugin DESTINATION ${GAZEBO_PLUGIN_PATH})

