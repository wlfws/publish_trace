#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <turtlesim/Pose.h>
void poseCallback(const tf2_msgs::TFMessage::ConstPtr& tf_msg){

}
int main(int argc, char** argv){
 ros::init(argc,argv,"my_trace");
 ros::NodeHandle node;
 ros::Subscriber sub = node.subscribe("/tf",10,&poseCallback);
 ros::spin();
 return 0;
};

