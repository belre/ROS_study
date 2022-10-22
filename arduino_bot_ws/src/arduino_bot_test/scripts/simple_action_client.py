
#!/usr/bin/env python3

import rospy
import actionlib
from arduino_bot_test.msg import FibonacciAction, FibonacciGoal


def fibonacci_client():
    client = actionlib.SimpleActionClient('fibonacci', FibonacciAction)
    client.wait_for_server()
    goal = FibonacciGoal(goal=20)
    print('sending goal order %s' % goal.goal)
    client.send_goal(goal)
    client.wait_for_result()
    return client.get_result()

if __name__ == '__main__':
    rospy.init_node('fibonacci_client')
    rospy.loginfo('simple action client started')
    result = fibonacci_client()
    print('result ', result.sequence)

