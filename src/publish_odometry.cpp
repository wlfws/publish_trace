#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <nav_msgs/Odometry.h>
#include <math.h>
int main(int argc, char** argv){
  ros::init(argc, argv, "my_publish_Odometry");
  ros::NodeHandle node;
  ros::Publisher odometry_pub =node.advertise<nav_msgs::Odometry>("robot/Odometry", 1);
  ros::Subscriber pose_with_covariance_sub;
  tf::TransformListener listener;
  ros::Rate rate(1.0);
  double pose_x=0,pose_y=0,length;
  double x,y,l;
  while (node.ok()){
    tf::StampedTransform transform;
    try{
        listener.waitForTransform("/map", "/base_link",ros::Time(0), ros::Duration(10.0) );
	listener.lookupTransform("/map", "/base_link",
                               ros::Time(0), transform);
    }
    catch (tf::TransformException &ex) {
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
      continue;
    }
    nav_msgs::Odometry odometry_msg;
    odometry_msg.header.stamp=ros::Time::now();
    odometry_msg.header.frame_id="map";
    odometry_msg.child_frame_id="base_link";
    odometry_msg.pose.pose.position.x=transform.getOrigin().x();
    odometry_msg.pose.pose.position.y=transform.getOrigin().y();
    odometry_msg.pose.pose.position.z=transform.getOrigin().z();
    odometry_msg.pose.pose.orientation.x=transform.getRotation().x();
    odometry_msg.pose.pose.orientation.y=transform.getRotation().y();
    odometry_msg.pose.pose.orientation.z=transform.getRotation().z();
    odometry_msg.pose.pose.orientation.w=transform.getRotation().w();
    x=odometry_msg.pose.pose.position.x;
    y=odometry_msg.pose.pose.position.y;
    length=sqrt((x-pose_x)*(x-pose_x) + (y-pose_y)*(y-pose_y));
    l=l+length;
    ROS_INFO("l=%lf",l);
    odometry_pub.publish(odometry_msg);
    rate.sleep();
  }
  return 0;
};
