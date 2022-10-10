
#!usr/bin/env   python3

import rospy
from arduino_bot_test.srv import AddTwoInts, AddTwoIntsResponse

def add_two_ints_callback(req):
    rospy.loginfo("Ready to sum %d and %d", req.a, req.b)
    return AddTwoIntsResponse(req.a + req.b)


if __name__ == "__main__":
    rospy.init_node('simple_service')
    service = rospy.Service('add_two_ints', AddTwoInts, add_two_ints_callback)
    rospy.loginfo("The service is ready to add ints")
    rospy.spin()
    
    
    








