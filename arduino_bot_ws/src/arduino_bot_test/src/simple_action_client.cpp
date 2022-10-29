
#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include "arduino_bot_test/FibonacciAction.h"

int main(int argc, char** argv) 
{
    ros::init(argc, argv, "fibonacci_client");
    actionlib::SimpleActionClient<arduino_bot_test::FibonacciAction> action_client("fibonacci");

    ROS_INFO("Waiting for action server to start");
    action_client.waitForServer();

    ROS_INFO("Action server started, sending a goal");
    arduino_bot_test::FibonacciGoal goal;
    goal.goal = 20;

    action_client.sendGoal(goal);

    action_client.waitForResult(ros::Duration(30.0));
    
    auto result = action_client.getResult();
    ROS_INFO("Action finished:");
    
    for(int i : result->sequence) {
        ROS_INFO("%d", i);
    }

    return 0;
}


