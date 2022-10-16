
#include "arduino_bot_controller/arduino_bot_interface.h"
#include <std_msgs/UInt16MultiArray.h>
#include "arduino_bot_controller/AnglesConverter.h"


ArduinoBotInterface::ArduinoBotInterface(ros::NodeHandle& nh) : _nh(nh),
                                                            _pnh("~"),
                                                            _position(4, 0),
                                                            _velocity(4, 0),
                                                            _effort(4, 0),
                                                            _cmd(4, 0),
                                                            _names{"joint_1", "joint2", "joint_3", "joint_4"}
{
    _hardware_pub = _pnh.advertise<std_msgs::UInt16MultiArray>("/arduino/arm_actuate", 1000);
    _hardware_srv = _pnh.serviceClient<arduino_bot_controller::AnglesConverter>("/radians_to_degrees");
    
    hardware_interface::JointStateHandle state_handle1(_names.at(0), &_position.at(0), &_velocity.at(0), &_effort.at(0));
    _joint_state_interface.registerHandle(state_handle1);

    hardware_interface::JointStateHandle state_handle2(_names.at(1), &_position.at(1), &_velocity.at(1), &_effort.at(1));
    _joint_state_interface.registerHandle(state_handle2);

    hardware_interface::JointStateHandle state_handle3(_names.at(2), &_position.at(2), &_velocity.at(2), &_effort.at(2));
    _joint_state_interface.registerHandle(state_handle3);

    hardware_interface::JointStateHandle state_handle4(_names.at(3), &_position.at(3), &_velocity.at(3), &_effort.at(3));
    _joint_state_interface.registerHandle(state_handle4);

    registerInterface(&_joint_state_interface);

    hardware_interface::JointHandle position_handle1(_joint_state_interface.getHandle(_names.at(0)), &_cmd.at(0));
    _joint_position_interface.registerHandle(position_handle1);

    hardware_interface::JointHandle position_handle2(_joint_state_interface.getHandle(_names.at(1)), &_cmd.at(1));
    _joint_position_interface.registerHandle(position_handle2);

    hardware_interface::JointHandle position_handle3(_joint_state_interface.getHandle(_names.at(2)), &_cmd.at(2));
    _joint_position_interface.registerHandle(position_handle3);

    hardware_interface::JointHandle position_handle4(_joint_state_interface.getHandle(_names.at(3)), &_cmd.at(3));
    _joint_position_interface.registerHandle(position_handle4);

    registerInterface(&_joint_position_interface);
    _controller_manager.reset(new controller_manager::ControllerManager(this, _nh));

    _update_freq = ros::Duration(0.1);
    _looper = _nh.createTimer(_update_freq, &ArduinoBotInterface::update, this);
}



ArduinoBotInterface::~ArduinoBotInterface() 
{

}

void ArduinoBotInterface::update(const ros::TimerEvent& event) 
{
    _elapsed_time = ros::Duration(event.current_real - event.last_real);
    read();

    _controller_manager->update(ros::Time::now(), _elapsed_time);
    write(_elapsed_time);
}

void ArduinoBotInterface::read() 
{
    _position.at(0) = _cmd.at(0);
    _position.at(1) = _cmd.at(1);
    _position.at(2) = _cmd.at(2);
    _position.at(3) = _cmd.at(3);
}

void ArduinoBotInterface::write(ros::Duration elapsed_time) 
{
    arduino_bot_controller::AnglesConverter srv;
    srv.request.base = _cmd.at(0);
    srv.request.shoulder = _cmd.at(1);
    srv.request.elbow = _cmd.at(2);
    srv.request.gripper = _cmd.at(3);

    if(_hardware_srv.call(srv)) 
    {
        std::vector<unsigned int> angles_deg;
        angles_deg.push_back(srv.response.base);
        angles_deg.push_back(srv.response.shoulder);
        angles_deg.push_back(srv.response.elbow);
        angles_deg.push_back(srv.response.gripper);

        std_msgs::UInt16MultiArray msg;
        msg.layout.dim.push_back(std_msgs::MultiArrayDimension());
        msg.layout.dim[0].size = angles_deg.size();
        msg.layout.dim[0].stride = 1;
        msg.data.clear();
        msg.data.insert(msg.data.end(), angles_deg.begin(), angles_deg.end());        

        _hardware_pub.publish(msg);
    }
    else
    {
        ROS_ERROR("Failed to call radians_to_degrees");
    }
}

int main(int argc, char** argv) 
{
    ros::init(argc, argv, "arduino_bot_interface_node");
    ros::NodeHandle nh;

    ros::MultiThreadedSpinner spinner(2);
    ArduinoBotInterface robot(nh);
    spinner.spin();

    return 0;
}
