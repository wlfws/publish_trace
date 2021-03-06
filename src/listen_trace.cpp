#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/PoseArray.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "my_tf_listener");

  ros::NodeHandle node;
  
  ros::Publisher trace_pub =
    node.advertise<geometry_msgs::PoseArray>("robot/trace", 10);

  tf::TransformListener listener;
  ros::Rate rate(10.0);
  int i=0;
  while (node.ok()){
    tf::StampedTransform transform;
    try{
       // listener.waitForTransform("/base_link", "/odom",ros::Time(0), ros::Duration(10.0) );
	listener.lookupTransform("/base_link", "/odom",
                               ros::Time(0), transform);
    }
    catch (tf::TransformException &ex) {
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
      continue;
    }

    geometry_msgs::PoseArray trace_msg;
    
    trace_msg.poses[i].position.x=transform.getOrigin().x();
    trace_msg.poses[i].position.y=transform.getOrigin().y();
    trace_msg.poses[i].position.z=transform.getOrigin().z();
    trace_msg.poses[i].orientation.x=transform.getRotation().x();
    trace_msg.poses[i].orientation.y=transform.getRotation().y();
    trace_msg.poses[i].orientation.z=transform.getRotation().z();
    trace_msg.poses[i].orientation.w=transform.getRotation().w();
    i++;
    trace_pub.publish(trace_msg);
    rate.sleep();
  }
  return 0;
};
