#!/usr/bin/env python

import serial
import rospy
from hexapod import Hexapod

PORT = '/dev/ttyACM0'
BAUD = 57600
CMD = {"enable_motors":"M17",
       "disable_motors":"M18",
       "set_speed":"F",
       "linear_move":"G01",
       "fast_move":"G00",
       "set_x":"X",
       "set_y":"Y",
       "set_z":"Z",
       "set_u":"U",
       "set_v":"V",
       "set_w":"W",
       "homing":"G28",
       "get_state":"M114"}

#TODO: handle serial port exceptions
class RumbaDriver:
    def __init__(self, port):
        print "Connecting to RUMBA board on port " + port + " at baud " + str(BAUD)
        self._ser = serial.Serial(port, BAUD, timeout = .2)
        self._ser.readlines()
        rospy.sleep(2)
        self._ser.write(CMD["homing"]+";")
        rospy.sleep(3)
        self._ser.readlines()
        print "Homing complete"
        self.h = Hexapod()

    def enable_motors(self):
        self._ser.write(CMD["enable_motors"]+";")
        rospy.sleep(0.1)

    def disable_motors(self):
        self._ser.write(CMD["disable_motors"]+";")
        rospy.sleep(0.1)

    #pose is dict of axis (x,y,z,u,v,w) and numerical value pairs
    def goto_pose(self, x=None, y=None, z=None, u=None, v=None, w=None, vel=None, linear=True, best_effort=True):
        if best_effort:
            (x,y,z,u,v,w) = self.h.best_effort_ik(x,y,z,u,v,w)
            print "Moving to pose: " + str(x) + " " + str(y) + " " + str(z) + " " + str(u) + " " + str(v) + " " + str(w) + " " + str(vel)
        else:
            if not self.h.check_ik(x,y,z,u,v,w):
                print "Invalid position. Not moving motors."
                return

        if linear:
            command = CMD["linear_move"]
        else:
            command = CMD["fast_move"]

        goal_vel = self.get_state()[6]
        if vel != None and vel > 0.01 and vel < 240:
            goal_vel = vel
        print "Goal velocity = " + str(goal_vel)
        self._ser.write(command + " " + CMD["set_speed"]+ str(goal_vel)+";")
        print self._ser.readlines()
        if x==None and y==None and z==None and u==None and v==None and w==None:
            return

        if linear:
            command = CMD["linear_move"]
        else:
            command = CMD["fast_move"] 
        
        if x != None:
            command += " " + CMD["set_x"]+str(round(x,1))
        if y != None:
            command += " " + CMD["set_y"]+str(round(y,1))
        if z != None:
            command += " " + CMD["set_z"]+str(round(z,1))
        if u != None:
            command += " " + CMD["set_u"]+str(round(u,1))
        if v != None:
            command += " " + CMD["set_v"]+str(round(v,1))
        if w != None:
            command += " " + CMD["set_w"]+str(round(w,1))

        command += ";"
       

        self._ser.write(command)
        print self._ser.readlines()

    def get_state(self):
        self._ser.write(CMD["get_state"] + ";");
        s = self._ser.readlines()
        #return s
        x = float(s[1].split('=')[1].split('\r')[0])
        y = float(s[2].split('=')[1].split('\r')[0])
        z = float(s[3].split('=')[1].split('\r')[0])
        u = float(s[4].split('=')[1].split('\r')[0])
        v = float(s[5].split('=')[1].split('\r')[0])
        w = float(s[6].split('=')[1].split('\r')[0])
        vel = float(s[7].split('=')[1].split('\r')[0])
        return (x,y,z,u,v,w,vel)

    def close(self):
        self._ser.write(CMD["disable_motors"]+";")
        rospy.sleep(2.0)

if __name__ == '__main__':
    r = RumbaDriver(PORT)

    z = 0
    max_z = 3
    my_vel = 220
    end_vel = 240

    r.goto_pose(z=3, vel=1)
    rospy.sleep(1)
    while my_vel < end_vel:
        my_vel = my_vel + 10
        r.goto_pose(vel=my_vel)
        print r.get_state()
        rospy.sleep(1)
    rospy.sleep(5)
    r.close()
    #print str(r.get_state())
    #r.goto_pose(z=3, vel=.01)
    #print str(r.get_state())
