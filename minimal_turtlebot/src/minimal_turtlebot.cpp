
#include<ros/ros.h> 
#include<std_msgs/Float64.h> 
#include<kobuki_msgs/WheelDropEvent.h>
#include<kobuki_msgs/BumperEvent.h>
#include<kobuki_msgs/Sound.h>
#include <geometry_msgs/Twist.h>

//instantiate some special types for our commands  
kobuki_msgs::Sound soundValue; 
geometry_msgs::Twist base_cmd;

uint8_t soundValueUpdateCounter = 0; 
  
uint8_t leftWheelDropped=0; 
uint8_t rightWheelDropped=0; 

uint8_t leftBumperPressed=0; 
uint8_t centerBumperPressed=0; 
uint8_t rightBumperPressed=0; 

void studentCode(void) 
{ 
	//Place your code here! you can access the left / right wheel 
	//dropped variables declared above, as well as information about
	//bumper status. 
	
	//outputs have been set to some default values. Feel free 
	//to change these constants to see how they impact the robot. 
	
	base_cmd.linear.x = 0.25; //FYI 1.0 is very fast so you have a frame
	//of reference. 
	
	base_cmd.angular.z = 0.0; 
	soundValue.value=soundValue.ERROR; 
	
	//here are the various sound value enumeration options
	//soundValue.OFF
	//soundValue.RECHARGE
	//soundValue.BUTTON
	//soundValue.ERROR
	//soundValue.CLEANINGSTART
	//soundValue.CLEANINGEND
} 


void wheelDropCallBack(const kobuki_msgs::WheelDropEvent& wheel_data_holder) 
{ 
	
	if (wheel_data_holder.wheel == wheel_data_holder.LEFT)
	{
		leftWheelDropped = wheel_data_holder.state; 
		ROS_INFO("left wheel dropped state is: %u",wheel_data_holder.state); 
	}
	
	if (wheel_data_holder.wheel == wheel_data_holder.RIGHT)
	{
		rightWheelDropped = wheel_data_holder.state; 
		ROS_INFO("right wheel dropped state is: %u",wheel_data_holder.state); 
	}

} 

void bumperMessageCallback(const kobuki_msgs::BumperEvent& bumper_data_holder) 
{ 
	if (bumper_data_holder.bumper == bumper_data_holder.LEFT)
	{
		leftBumperPressed = bumper_data_holder.state; 
		ROS_INFO("left bumper pressed state is: %u",bumper_data_holder.state); 
	}
	
	if (bumper_data_holder.bumper == bumper_data_holder.CENTER)
	{
		centerBumperPressed = bumper_data_holder.state; 
		ROS_INFO("center bumper pressed state is: %u",bumper_data_holder.state); 
	}
	
	if (bumper_data_holder.bumper == bumper_data_holder.RIGHT)
	{
		rightBumperPressed = bumper_data_holder.state; 
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
  
  //publish sound and command vel messages 
  
  ros::Publisher my_publisher_object = n.advertise<kobuki_msgs::Sound>("mobile_base/commands/sound", 1);
  ros::Publisher cmd_vel_pub_ = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
  
  while(ros::ok())
  {
	ros::spinOnce();

	studentCode(); 
	
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
