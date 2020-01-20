cmake_minimum_required(VERSION 2.8.3)
project(fac_demo)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    rospy
    std_msgs
    nav_msgs
    geometry_msgs
    tf
)

catkin_package()

include_directories(
    ${catkin_INCLUDE_DIRS}
)

add_executable(fac_demo src/fac_demo.cpp)
target_link_libraries(fac_demo ${catkin_LIBRARIES})
