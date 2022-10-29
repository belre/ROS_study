#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include "arduino_bot_test/FibonacciAction.h"

class FibonacciActionServer 
{
public:
    ros::NodeHandle _nh;
    actionlib::SimpleActionServer<arduino_bot_test::FibonacciAction> _as;
    std::string _action_name;
    arduino_bot_test::FibonacciFeedback _feedback;
    arduino_bot_test::FibonacciResult _result;

    FibonacciActionServer(std::string name)
        : _as(_nh, name, boost::bind(&FibonacciActionServer::ExecuteCallback, this, _1), false),
          _action_name(name)
    {
        _as.start();
        ROS_INFO("Simple action server started");

    }

    void ExecuteCallback(const arduino_bot_test::FibonacciGoalConstPtr &goal) 
    {
        ROS_INFO("Goal Received %i", goal->goal);
        ros::Rate rate(1);
        bool success = true;
        
        _feedback.sequence.clear();
        _feedback.sequence.push_back(1);
        _feedback.sequence.push_back(1);

        for( int i = 1; i < goal->goal; i ++)
        {
            if(_as.isPreemptRequested() || !ros::ok())
            {
                ROS_INFO("%s is Preempted", _action_name.c_str());
                _as.setPreempted();
                success = false;
                break;
            }

            _feedback.sequence.push_back(_feedback.sequence[i] + _feedback.sequence[i-1]);
            _as.publishFeedback(_feedback);
            rate.sleep();
        }

        if(success) 
        {
            _result.sequence = _feedback.sequence;
            ROS_INFO("%s is succeeded", _action_name.c_str());
            _as.setSucceeded(_result);
        }
    }


    virtual ~FibonacciActionServer() 
    {

    }


};

int main(int argc, char** argv) 
{
    ros::init(argc, argv, "fibonacci");
    FibonacciActionServer fibonacci_srv("fibonacci");
    
    ros::spin();

    return 0;
}






