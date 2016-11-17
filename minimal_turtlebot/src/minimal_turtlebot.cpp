
#include<ros/ros.h> 
#include<std_msgs/Float64.h> 
#include<kobuki_msgs/WheelDropEvent.h>
#include<kobuki_msgs/BumperEvent.h>
#include<kobuki_msgs/Sound.h>
#include <geometry_msgs/Twist.h>
#include "minimal_turtlebot/turtlebot_controller.h"
#include <sensor_msgs/CompressedImage.h>
#include <sensor_msgs/Image.h>

//instantiate some special types for our commands  
kobuki_msgs::Sound soundValue; 
geometry_msgs::Twist base_cmd;

uint8_t localSoundValue=0; 
float localLinearSpeed=0.0; 
float localAngularSpeed=0.0; 

uint8_t soundValueUpdateCounter = 0; 
  
turtlebotInputs localTurtleBotInputs; 

void colorImageCallback(const sensor_msgs::Image& image_data_holder) 
{ 
	static uint32_t colorImageInfoCounter = 0; 
	
	localTurtleBotInputs.colorImage=image_data_holder; 
	if (colorImageInfoCounter > 30)
	{
		ROS_INFO("color image height: %u",image_data_holder.height);
		ROS_INFO("color image width: %u",image_data_holder.width);
		colorImageInfoCounter=0; 
	}
	else
	{
		colorImageInfoCounter++; 
	}

} 

void depthImageCallback(const sensor_msgs::Image& image_data_holder) 
{ 
	static uint32_t depthImageInfoCounter = 0; 
	
	localTurtleBotInputs.depthImage=image_data_holder; 
	if (depthImageInfoCounter > 1)
	{
		ROS_INFO("depth image height: %u",image_data_holder.height);
		ROS_INFO("depth image width: %u",image_data_holder.width);
		//ROS_INFO("depth image encoding: %s",image_data_holder.encoding.c_str());
		depthImageInfoCounter=0; 
	}
	else
	{
		depthImageInfoCounter++; 
	}
} 


void wheelDropCallBack(const kobuki_msgs::WheelDropEvent& wheel_data_holder) 
{ 
	
	if (wheel_data_holder.wheel == wheel_data_holder.LEFT)
	{
		localTurtleBotInputs.leftWheelDropped = wheel_data_holder.state; 
		ROS_INFO("left wheel dropped state is: %u",wheel_data_holder.state); 
	}
	
	if (wheel_data_holder.wheel == wheel_data_holder.RIGHT)
	{
		localTurtleBotInputs.rightWheelDropped = wheel_data_holder.state; 
		ROS_INFO("right wheel dropped state is: %u",wheel_data_holder.state); 
	}

} 

void bumperMessageCallback(const kobuki_msgs::BumperEvent& bumper_data_holder) 
{ 
	if (bumper_data_holder.bumper == bumper_data_holder.LEFT)
	{
		localTurtleBotInputs.leftBumperPressed = bumper_data_holder.state; 
		ROS_INFO("left bumper pressed state is: %u",bumper_data_holder.state); 
	}
	
	if (bumper_data_holder.bumper == bumper_data_holder.CENTER)
	{
		localTurtleBotInputs.centerBumperPressed = bumper_data_holder.state; 
		ROS_INFO("center bumper pressed state is: %u",bumper_data_holder.state); 
	}
	
	if (bumper_data_holder.bumper == bumper_data_holder.RIGHT)
	{
		localTurtleBotInputs.rightBumperPressed = bumper_data_holder.state; 
		ROS_INFO("right bumper pressed state is: %u",bumper_data_holder.state); 
	}

} 

int main(int argc, char **argv) 
{ 
  ros::init(argc,argv,"my_minimal_subscriber"); //name this node 
  // when this compiled code is run, ROS will recognize it as a node called "minimal_subscriber" 
  ros::NodeHandle n; // need this to establish communications with our new node 
  //create a Subscriber object and have it subscribe to the topic "topic1" 
  // the function "myCallback" will wake up whenever a new message is published to topic1 
  // the real work is done inside the callback function 
  
  ros::Rate naptime(10); // use to regulate loop rate 
  
  //subscribe to wheel drop and bumper messages
  ros::Subscriber my_wheel_drop_subscription= n.subscribe("mobile_base/events/wheel_drop",1,wheelDropCallBack); 
  ros::Subscriber my_bumper_subscription= n.subscribe("mobile_base/events/bumper",1,bumperMessageCallback); 
  ros::Subscriber colorImageSubscription= n.subscribe("camera/rgb/image_rect_color",1,colorImageCallback); 
  ros::Subscriber depthSubscription= n.subscribe("camera/depth/image_raw",1,depthImageCallback); 
  
  //publish sound and command vel messages 
  
  ros::Publisher my_publisher_object = n.advertise<kobuki_msgs::Sound>("mobile_base/commands/sound", 1);
  ros::Publisher cmd_vel_pub_ = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
  

  
  while(ros::ok())
  {
	ros::spinOnce();
	turtlebot_controller(localTurtleBotInputs, &localSoundValue, &localLinearSpeed, &localAngularSpeed);
	
	soundValue.value=localSoundValue;
	base_cmd.linear.x=localLinearSpeed;
	base_cmd.angular.z=localAngularSpeed;
	
	if (soundValueUpdateCounter > 10)
	{
		my_publisher_object.publish(soundValue); 
		soundValueUpdateCounter = 0; 
	}
	else
	{
		soundValueUpdateCounter++;
	}
	
	cmd_vel_pub_.publish(base_cmd);
	
	naptime.sleep(); 
	
  }
  return 0; // should never get here, unless roscore dies 
} 

