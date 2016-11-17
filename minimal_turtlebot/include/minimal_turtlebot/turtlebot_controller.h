#ifndef TURTLEBOT_CONTROLLER
#define TURTLEBOT_CONTROLLER

#include <stdint.h>
#include <sensor_msgs/Image.h>



struct turtlebotInputs
{
	//wheel drop states
	uint8_t leftWheelDropped;
	uint8_t rightWheelDropped; 
	
	//bumper states 
	uint8_t leftBumperPressed; 
	uint8_t centerBumperPressed;
	uint8_t rightBumperPressed;
	
	//color and depth images
	sensor_msgs::Image colorImage;  
	sensor_msgs::Image depthImage;  
	
};

void turtlebot_controller(turtlebotInputs turtlebot_inputs, uint8_t *soundValue, float *vel, float *ang_vel);
#endif
