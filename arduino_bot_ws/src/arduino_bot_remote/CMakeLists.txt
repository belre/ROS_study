cmake_minimum_required(VERSION 3.0.2)
project(arduino_bot_remote)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  actionlib
  message_generation
  moveit_ros_planning_interface
)

add_action_files(
  FILES 
  ArduinoBotTask.action
)

generate_messages(
  DEPENDENCIES
  std_msgs
  actionlib_msgs
)

catkin_package(

)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

catkin_install_python(
  PROGRAMS
  scripts/task_server.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
