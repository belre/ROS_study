#!/usr/bin/env python3

import rospy
import actionlib
from arduino_bot_remote.msg import ArduinoBotTaskAction, ArduinoBotTaskResult
import sys
import moveit_commander

class TaskServer(object):
    _result = ArduinoBotTaskResult()
    arm_goal = []
    gripper_goal = []


    def __init__(self, name):
        self._action_name = name
        moveit_commander.roscpp_initialize(sys.argv)
        self._arm_move_group = moveit_commander.MoveGroupCommander("arduino_bot_arm")
        self._hand_move_group = moveit_commander.MoveGroupCommander("arduino_bot_hand")
        self._as = actionlib.SimpleActionServer(self._action_name, ArduinoBotTaskAction, \
                                                execute_cb = self.execute_callback, auto_start=False)
        self._as.start()
        
    def execute_callback(self, goal):
        success = True
        
        rospy.loginfo('%d is task_number' % goal.task_number)
        
        if goal.task_number == 0:
            self.arm_goal = [0.0, 0.0, 0.0]
            self.gripper_goal = [-0.7, 0.7]
        elif goal.task_number == 1:
            self.arm_goal = [-1.14, -0.6, -0.07]
            self.gripper_goal = [0.0, 0.0]
        elif goal.task_number == 2:
            self.arm_goal = [-1.57, 0.0, -1.0]
            self.gripper_goal = [0.0, 0.0]
        else:
            rospy.logerr('Invalid goal')
            return
        
        self._arm_move_group.go(self.arm_goal, wait=True)
        self._hand_move_group.go(self.gripper_goal, wait=True)
        
        self._arm_move_group.stop()
        self._hand_move_group.stop()
        
        if self._as.is_preempt_requested():
            rospy.loginfo('%s is Preempted' % self._action_name )
            self._as.set_preempted()
            success = False
            
        if success:
            self._result.success = True
            rospy.loginfo('%s Succeeded' % self._action_name)
            self._as.set_succeeded(self._result)


if __name__ == '__main__':
    rospy.init_node('task_server')
    server = TaskServer('task_server')
    rospy.spin()




