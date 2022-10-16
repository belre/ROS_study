
#include <ros/ros.h>
#include "arduino_bot_controller/AnglesConverter.h"
#include <cmath>

bool convert_radians_to_degrees(arduino_bot_controller::AnglesConverter::Request &req,
                                arduino_bot_controller::AnglesConverter::Response &res) 
{
    res.base = static_cast<int>(((req.base + (M_PI / 2)) * 180) / M_PI);
    res.shoulder = 180 - static_cast<int>(((req.shoulder + (M_PI / 2)) * 180) / M_PI);
    res.elbow = static_cast<int>(((req.elbow + (M_PI / 2)) * 180 ) / M_PI); 
    res.gripper = static_cast<int>(((-req.gripper) * 180) / (M_PI / 2));

    return true;
}

bool convert_degrees_to_radians(arduino_bot_controller::AnglesConverter::Request &req,
                                arduino_bot_controller::AnglesConverter::Response &res) 
{
    res.base = ((M_PI * req.base) - ((M_PI / 2) * 180)) / 180;
    res.shoulder = (((180 - req.shoulder) * M_PI) - ((M_PI / 2) * 180)) / 180;
    res.elbow = ((M_PI * req.elbow) - ((M_PI / 2) * 180) / 180);
    res.gripper = -((M_PI/2) * req.gripper) / 180;

    return true;
}


int main(int argc, char** argv) 
{
    ros::init(argc, argv, "angles_converter");
    ros::NodeHandle nh;
    ros::ServiceServer radians_to_degrees = nh.advertiseService("radians_to_degrees", convert_radians_to_degrees);
    ros::ServiceServer degrees_to_radians = nh.advertiseService("degrees_to_radians", convert_degrees_to_radians);

    ros::spin();

    return 0;
}






