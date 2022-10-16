cmake_minimum_required(VERSION 3.0.2)
project(arduino_bot_controller)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
  controller_manager
  hardware_interface
)

add_service_files(
  FILES
  AnglesConverter.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  INCLUDE_DIRS
    include
  CATKIN_DEPENDS
    controller_manager
    hardware_interface
)

include_directories(simple_cpp_service
  include
  ${catkin_INCLUDE_DIRS}
)

catkin_install_python(
  PROGRAMS
    scripts/angles_converter.py
  DESTINATION
    ${CATKIN_PACKAGE_BIN_DESTINATION}
)

add_executable(angles_converter_cpp src/angles_cpp_converter.cpp)
add_dependencies(angles_converter_cpp ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(angles_converter_cpp ${catkin_LIBRARIES})

add_executable(arduino_bot_interface_node src/arduino_bot_interface.cpp)
add_dependencies(arduino_bot_interface_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(arduino_bot_interface_node ${catkin_LIBRARIES})


