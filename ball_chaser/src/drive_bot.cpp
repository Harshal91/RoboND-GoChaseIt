#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"

ros::Publisher motor_command_publisher;


bool handle_drive_request(ball_chaser::DriveToTarget::Request& req, ball_chaser::DriveToTarget::Response& res)
{

  while(ros::ok())
    {

      geometry_msgs::Twist motor_command;

      motor_command.linear.x = req.linear_x;
      motor_command.angular.z = req.angular_z;

      motor_command_publisher.publish(motor_command);     
  
      res.msg_feedback = "Wheel Command Supplied !";

      ROS_INFO_STREAM(res.msg_feedback);

      return true;
      
      
    }
  
}


int main(int argc,char** argv)
{
  //Initialize a Ros node
  ros::init(argc,argv,"drive_bot");

  //Create ROS NodeHangle Object;
  ros::NodeHandle n;

  //Inform ROS master that we will publish a message of type
  // geometry_msgs::Twist on robot actuation topic wit qeue of 10

  motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel",10);

  ros::ServiceServer service = n.advertiseService("/ball_chaser/command_robot",handle_drive_request);

  //Handle ROS comm

  ros::spin();
  return 0;
  
}
