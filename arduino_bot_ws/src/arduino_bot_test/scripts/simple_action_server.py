#!/usr/env/bin python3

import rospy
import actionlib
from arduino_bot_test.msg import FibonacciAction, FibonacciResult, FibonacciFeedback


class FibonacciActionServer(object):
    _feedback = FibonacciFeedback()
    _result = FibonacciResult()
    
    def __init__(self, name):
        self._action_name = name
        self._as = actionlib.SimpleActionServer(self._action_name, FibonacciAction, execute_cb=self.execute_callback, auto_start=False)
        self._as.start()
        rospy.loginfo('Simple Action Server Started')
    
    def execute_callback(self, goal, ):
        rospy.loginfo('Goal Received %s' % goal.goal)
        r = rospy.Rate(1)
        success = True    
        self._feedback.sequence = []
        self._feedback.sequence.append(1)
        self._feedback.sequence.append(1)

        for i in range(1, goal.goal - 1):
            if self._as.is_preempt_requested():
                rospy.loginfo('%s Preempted' % self._action_name)
                self._as.set_preempted()
                success = False
                break
             
            self._feedback.sequence.append(self._feedback.sequence[i] + self._feedback.sequence[i-1])
            self._as.publish_feedback(self._feedback)
            r.sleep()

        if success:
            self._result.sequence = self._feedback.sequence
            rospy.loginfo('%s Succeeded' % self._action_name)
            self._as.set_succeeded(self._result)

if __name__ == '__main__':
    rospy.init_node('fibonacci')
    server = FibonacciActionServer('fibonacci')
    rospy.spin()
