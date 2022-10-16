
#include <ros/ros.h>
#include "arduino_bot_test/AddTwoInts.h"

bool add_two_ints_callback( arduino_bot_test::AddTwoInts::Request &req,
                            arduino_bot_test::AddTwoInts::Response &res) 
{
    ROS_INFO("ready to sum %d and %d", req.a, req.b);
    res.sum = req.a + req.b;

    return true;
}

int main(int argc, char** argv) 
{
    ros::init(argc, argv, "simple_service");
    ros::NodeHandle nh;
    ros::ServiceServer service = nh.advertiseService("add_two_ints", add_two_ints_callback);

    ROS_INFO("The service is ready to add ints");

    ros::spin();
    return 0;
}

