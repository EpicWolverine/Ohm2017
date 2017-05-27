#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

#include <string>

ros::Publisher cartesianPub;

void conversionCallback(const geometry_msgs::Twist::ConstPtr& msg){
    lastOverride = Clock::now();
	autoPub.publish(*msg);

	ROS_INFO("Auto Control: override linear.x=%f angular.z=%f", msg->linear.x, msg->angular.z);
}

int main(int argc, char **argv){
	ros::init(argc, argv, "polar_to_cartesian");

	ros::NodeHandle n;

    string topicSuffix;
    n.param("polar_to_cartesian_topic_suffix", topicSuffix, "1");

	cartesianPub = n.advertise<geometry_msgs::Twist>("cartesianOut-" + topicSuffix, 1000);

	ros::Subscriber polarSub = n.subscribe("polarIn-" + topicSuffix, 1000, conversionCallback);

	ros::spin();
	
	return 0;
}