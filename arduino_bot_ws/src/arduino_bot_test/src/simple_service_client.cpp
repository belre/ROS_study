#include <ros/ros.h>
#include "arduino_bot_test/AddTwoInts.h"


int main(int argc, char** argv) 
{
    ros::init(argc, argv, "add_two_ints");

    if(argc != 3) 
    {
       ROS_ERROR("Requested two arguments");
       return 1;     
    }


    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<arduino_bot_test::AddTwoInts>("add_two_ints");
    arduino_bot_test::AddTwoInts srv;
    srv.request.a = std::atoll(argv[1]);
    srv.request.b = std::atoll(argv[2]);

    ROS_INFO("Requesting %d + %d", srv.request.a, srv.request.b);
    if( client.call(srv) )
    {
        ROS_INFO("Service Response %d", srv.response.sum);
    }
    else
    {
        ROS_ERROR("Failed to call the service add_two_ints");
    }

    return 0; 
}



