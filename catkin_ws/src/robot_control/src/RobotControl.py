#!/usr/bin/env python
"""
ROS based interface for the Course Robotics Specialization Capstone Autonomous Rover.
Updated June 19 2016.
"""
import os
import rospy
import yaml
import numpy as np

import sys

# TODO for student: Comment this section when running on the robot 
# from RobotSim import RobotSim
# import matplotlib.pyplot as plt

# TODO for student: uncomment when changing to the robot
from RosInterface import ROSInterface
from nav_msgs.msg import Odometry
# TODO for student: User files, uncomment as completed
#from MyShortestPath import dijkstras
#from KalmanFilter import KalmanFilter

frequence = 10
dt = 1./frequence

from DiffDriveController import DiffDriveController

class RobotControl(object):
    """
    Class used to interface with the rover. Gets sensor measurements through ROS subscribers,
    and transforms them into the 2D plane, and publishes velocity commands.
    """
    def __init__(self, world_map,occupancy_map, pos_init, pos_goal, max_speed, max_omega, x_spacing, y_spacing, t_cam_to_body):
        """
        Initialize the class
        Inputs: (all loaded from the parameter YAML file)
        world_map - a P by 4 numpy array specifying the location, orientation,
            and identification of all the markers/AprilTags in the world. The
            format of each row is (x,y,theta,id) with x,y giving 2D position,
            theta giving orientation, and id being an integer specifying the
            unique identifier of the tag.
        occupancy_map - an N by M numpy array of boolean values (represented as
            integers of either 0 or 1). This represents the parts of the map
            that have obstacles. It is mapped to metric coordinates via
            x_spacing and y_spacing
        pos_init - a 3 by 1 array specifying the initial position of the robot,
            formatted as usual as (x,y,theta)
        pos_goal - a 3 by 1 array specifying the final position of the robot,
            also formatted as (x,y,theta)
        max_speed - a parameter specifying the maximum forward speed the robot
            can go (i.e. maximum control signal for v)
        max_omega - a parameter specifying the maximum angular speed the robot
            can go (i.e. maximum control signal for omega)
        x_spacing - a parameter specifying the spacing between adjacent columns
            of occupancy_map
        y_spacing - a parameter specifying the spacing between adjacent rows
            of occupancy_map
        t_cam_to_body - numpy transformation between the camera and the robot
            (not used in simulation)
        """

        # Comment this when running on the robot 
        # self.robot_sim = RobotSim(world_map, occupancy_map, pos_init, pos_goal,
        #                          max_speed, max_omega, x_spacing, y_spacing)
        # Use this when transferring code to robot
        # Handles all the ROS related items
        self.ros_interface = ROSInterface(t_cam_to_body)

        #self.kalman_filter = KalmanFilter(world_map)
        #self.diff_drive_controller = DiffDriveController(max_speed, max_omega)

    def process_measurements(self):
        """ 
        Main loop of the robot - where all measurements, control, and esimtaiton
        are done. This function is called at 60Hz

        """
        #: Comment this line for tracking
        return

        #: Use this when transferring code to robot
        goal_pos = self.ros_interface.get_measurements()
        fusion = self.ros_interface.get_fusion()
        #vel_meas = self.ros_interface.get_vel()
        if fusion is None: 
            #rospy.loginfo('fusion is none')
            return

        if goal_pos is None:
            #rospy.loginfo('goal is none')
            return
        #rospy.loginfo('measurement [x,y,th]: [%f %f %f]', goal_pos[0][0], goal_pos[1][0], goal_pos[2][0])
        #rospy.loginfo('current pos [x,y,th]: [%f %f %f]', fusion.pose.pose.position.x, fusion.pose.pose.position.y, fusion.pose.pose.orientation.z)
        
        (v,omg,done) = self.diff_drive_controller.compute_vel(np.matrix([[fusion.pose.pose.position.x,fusion.pose.pose.position.y,fusion.pose.pose.orientation.z]]).T, goal_pos)
        #(v,omg,done) = self.diff_drive_controller.compute_vel(np.matrix([[0,0,0]]).T, goal_pos)
        rospy.loginfo('v and omage is: [%f %f]', v, omg)

        if done == True:
            rospy.loginfo('Done')
            self.ros_interface.command_vel(0, 0)
        else:
            self.ros_interface.command_vel(v, omg)
        return

def main(args):
    # Load parameters from yaml
    BASE_DIR = os.path.abspath('..')
    param_path = BASE_DIR + '/catkin_ws/src/robot_control/params/week4.yaml'
    #rospy.get_param("week4.yaml")
    f = open(param_path,'r')
    params_raw = f.read()
    f.close()
    params = yaml.load(params_raw)
    occupancy_map = np.array(params['occupancy_map'])
    world_map = np.array(params['world_map'])
    pos_init = np.array(params['pos_init'])
    pos_goal = np.array(params['pos_goal'])
    max_vel = params['max_vel']
    max_omega = params['max_omega']
    t_cam_to_body = np.array(params['t_cam_to_body'])
    x_spacing = params['x_spacing']
    y_spacing = params['y_spacing']

    rospy.init_node('Tracking_Robot', anonymous=True)

    # Intialize the RobotControl object
    robotControl = RobotControl(world_map, occupancy_map, pos_init, pos_goal,
                                max_vel, max_omega, x_spacing, y_spacing,
                                t_cam_to_body)

    # TODO: Comment this when running on the robot 
    # Run the simulation
    # while not robotControl.robot_sim.done and plt.get_fignums():
    #    robotControl.process_measurements()
    #    robotControl.robot_sim.update_frame()

    #plt.ioff()
    #plt.show()

    # TODO: Use this to run the interface on the robot
    # Call process_measurements at 60Hz
    
    r = rospy.Rate(frequence)
    while not rospy.is_shutdown():
        robotControl.process_measurements()
        r.sleep()
    # Done, stop robot
    robotControl.ros_interface.command_vel(0,0)

if __name__ == "__main__":
    main(sys.argv)


