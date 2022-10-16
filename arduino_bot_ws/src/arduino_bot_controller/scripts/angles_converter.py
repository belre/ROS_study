#!/usr/bin/env python3

import rospy
from arduino_bot_controller.srv import AnglesConverter, AnglesConverterResponse
import math

def convert_radians_to_degrees(req):
    res = AnglesConverterResponse()
    res.base = int(((req.base + math.pi / 2) * 180) / math.pi)
    res.shoulder = 180 - int(((req.shoulder + math.pi / 2) * 180) / math.pi)
    res.elbow = int(((req.elbow + math.pi / 2) * 180) / math.pi)
    res.gripper = int(((-req.gripper) * 180) / (math.pi/2))
    return res

def convert_degrees_to_radians(req):
    res = AnglesConverterResponse()
    res.base = ((math.pi * req.base) - ((math.pi / 2) * 180)) / 180
    res.shoulder = (((180 - req.shoulder) * math.pi) - ((math.pi / 2) * 180)) / 180
    res.elbow = ((math.pi * req.elbow) - ((math.pi / 2 ) * 180)) / 180
    res.gripper = -((math.pi / 2) * req.gripper) / 180
    return res

if __name__ == "__main__":
    rospy.init_node('angles_converter')
    radians_to_degrees = rospy.Service('radians_to_degrees', AnglesConverter, convert_radians_to_degrees)
    degrees_to_radians = rospy.Service('degrees_to_radians', AnglesConverter, convert_degrees_to_radians)
    rospy.spin()    

