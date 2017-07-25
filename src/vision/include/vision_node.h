#ifndef VISION_NODE_H
#define VISION_NODE_H

//opencv includes
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>

//Vimba includes
#include <VimbaCPP/Include/VimbaCPP.h>
#include <VimbaImageTransform/Include/VmbTransform.h>

#include <iostream>
#include <stdio.h>
#include <chrono>

//ros includes
#include "ros/ros.h"
#include <ram_msgs/VisionNavAction.h>
#include <actionlib/server/simple_action_server.h>

//message includes
#include "std_msgs/String.h"
#include  "ram_msgs/bool_bool.h"

//our actions/tuner actions
#include "buoy_action.h"
#include "gate_action.h"

class VisionNode{

    public:


    //you need to pass in a node handle and a camera feed, which should be a file path either to a physical device or to a video file
    VisionNode(ros::NodeHandle n, ros::NodeHandle np,  std::string feed);
    ~VisionNode();
    void update(); //this will just pull the next image in


    //all service prototypes should go below, you also need to add a service variable for it in here and actually register
    //it in the constructor
    //=================================================================================================================


    bool serviceTest(ram_msgs::bool_bool::Request &req, ram_msgs::bool_bool::Response &res);


    //sg: put action definitions here
    //=================================================================================================================

    static void testExecute(const ram_msgs::VisionNavGoalConstPtr& goal, actionlib::SimpleActionServer<ram_msgs::VisionNavAction>*as);

    void findBuoy(const ram_msgs::VisionNavGoalConstPtr& goal, actionlib::SimpleActionServer<ram_msgs::VisionNavAction> *as);
    void findGate(const ram_msgs::VisionNavGoalConstPtr& goal, actionlib::SimpleActionServer<ram_msgs::VisionNavAction> *as);

    protected:

    //camera stuff
    //======================================================================
    AVT::VmbAPI::CameraPtr m_gige_camera;
    void getVmbFrame(cv::Mat& cv_frame);
    long m_width, m_height;
    VmbInt64_t m_pixel_format;

    cv::VideoCapture m_cap;
    cv::Mat m_img;

    cv::VideoWriter m_output_video;

    //declare a service object for your service below
    //======================================================================
    ros::ServiceServer m_test_srv;


    //declare an action server object for your action here
    //======================================================================
    //the VisionNavAction name here comes from the .action file in qubo/ram_msgs/action.
    //the build system appends the word Action to whatever the file name is in the ram_msgs directory
    actionlib::SimpleActionServer<ram_msgs::VisionNavAction> m_buoy_server;
    actionlib::SimpleActionServer<ram_msgs::VisionNavAction> m_gate_server;

};


#endif
