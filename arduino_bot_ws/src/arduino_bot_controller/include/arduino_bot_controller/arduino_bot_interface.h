#pragma once

#include <hardware_interface/robot_hw.h>
#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/joint_command_interface.h>
#include <controller_manager/controller_manager.h>
#include <ros/ros.h>
#include <boost/scoped_ptr.hpp>


class ArduinoBotInterface : public hardware_interface::RobotHW 
{
public:
    ArduinoBotInterface(ros::NodeHandle&);
    virtual ~ArduinoBotInterface();

    void update(const ros::TimerEvent&);
    void read();
    void write(ros::Duration);

private:
    ros::NodeHandle _nh;
    ros::NodeHandle _pnh;
    ros::Duration _elapsed_time;
    ros::Duration _update_freq;
    ros::Timer _looper;
    ros::Publisher _hardware_pub;
    ros::ServiceClient _hardware_srv;
    hardware_interface::JointStateInterface _joint_state_interface;
    hardware_interface::PositionJointInterface _joint_position_interface;
    boost::shared_ptr<controller_manager::ControllerManager> _controller_manager;
    std::vector<double> _cmd;
    std::vector<double> _position;
    std::vector<double> _velocity;
    std::vector<double> _effort;
    std::vector<std::string> _names;
};

