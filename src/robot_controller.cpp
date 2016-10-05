#include<ros/ros.h> 
#include<std_msgs/Float64.h> 
#include <stdr_msgs/CO2SensorMeasurementMsg.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <math.h> 

#include "braitenberg_vehicles/cmd_vel_eq.h"

#define ENABLE_ROBOT_STUCK_ACTION 0//adjust this if you'd like to disable the robot's stuck action 

float g_co2_sensor_0_ppm=0; 
float g_co2_sensor_1_ppm=0; 

float g_x_coordinate=0; 
float g_y_coordinate=0; 

geometry_msgs::Twist base_cmd;

void updateCO2Sensor0(const stdr_msgs::CO2SensorMeasurementMsg::ConstPtr& message_holder) 
{ 
  
  //Now let's update our global variable so you can do something with it 
  //In the while loop below. We'll keep things simple and only use the most recent
  //Value
  
  g_co2_sensor_0_ppm=message_holder->co2_ppm;
  
  //First let's send our received value to the cmd line so we can 
  //be aware of what we're reading 
  ROS_INFO("received co2 sensor 0 ppm is %f", g_co2_sensor_0_ppm); 
  
} 

void updateCO2Sensor1(const stdr_msgs::CO2SensorMeasurementMsg::ConstPtr& message_holder) 
{ 
  //Now let's update our global variable so you can do something with it 
  //In the while loop below. We'll keep things simple and only use the most recent
  //Value
  
  
  g_co2_sensor_1_ppm=message_holder->co2_ppm;
  //First let's send our received value to the cmd line so we can 
  //be aware of what we're reading 
  ROS_INFO("received sensor 1 ppm is %f",g_co2_sensor_1_ppm); 
  
} 

bool areWeStuck(float xCoord, float yCoord)
{
	static float previousXCoord = 0; 
	static float previousYCoord = 0; 
	
	float xCoordDifference=0; 
	float yCoordDifference=0; 
	
	xCoordDifference=fabs(xCoord-previousXCoord); 
	yCoordDifference=fabs(yCoord-previousYCoord); 
	
	//now let's update our previous coordinates for the next time this function is called
	previousXCoord=xCoord; 
	previousYCoord=yCoord; 
	
	ROS_INFO("xCoordDifference %f", xCoordDifference); 
	ROS_INFO("yCoordDifference %f", yCoordDifference); 
	
	if (xCoordDifference < 0.001 && yCoordDifference < 0.001)
	{
		ROS_INFO("We're stuck!!"); 
		return true; // we're def stuck :(
		
	}
	
	else 
	{
		ROS_INFO("We're not stuck!!!"); 
		return false; // still movin! 
	}
}

void updateLocalOdometryInformation(const nav_msgs::Odometry& odom_info) 
{ 
   //Now let's update our global variable so you can do something with it 
  //In the while loop below. 
  
  g_x_coordinate=odom_info.pose.pose.position.x;
  g_y_coordinate=odom_info.pose.pose.position.y;
  
  //First let's send our received value to the cmd line so we can 
  //be aware of what we're reading 
  ROS_INFO("received sensor x coordinate is %f", g_x_coordinate); 
  ROS_INFO("received sensor y coordinate is %f", g_y_coordinate); 
} 

int main(int argc, char **argv) 
{ 
  ROS_INFO("Here we are in the robot thermal controller init code");
  
  ros::init(argc,argv,"robot_controller"); //name this node 
  // when this compiled code is run, ROS will recognize it as a node called "robot_controller" 
  ros::NodeHandle n; // need this to establish communications with our new node 
  //We'll create a series of subscriber objectes for each of the thermal sensors we expect to have
  
  ros::Rate naptime(1); //create a ros object from the ros “Rate” class; 
  // set our while loop to run at 1 Hz 
  ros::Subscriber co2_sensor_0= n.subscribe("robot0/co2_sensor_0",1,updateCO2Sensor0); 
  ros::Subscriber co2_sensor_1= n.subscribe("robot0/co2_sensor_1",1,updateCO2Sensor1);
  ros::Subscriber robot_geometry= n.subscribe("robot0/odom",1,updateLocalOdometryInformation); 
  
  //set up the publisher for the cmd_vel topic
  ros::Publisher cmd_vel_pub_ = n.advertise<geometry_msgs::Twist>("/robot0/cmd_vel", 1);
  
  base_cmd.linear.x = base_cmd.linear.y = base_cmd.angular.z = 0; //initialize all vel cmd components
  //to zero 
  
  uint8_t state=0; 
  uint8_t stateCounter=0; 
  
  float desiredXVel=0; 
  float desiredZVel=0; 

  while (ros::ok())	
  {
	ros::spinOnce(); //let's spin at the top of our loop so we know we've got some good info to act on
	

	// !!!!!!!!!!!!!!!!! YOUR CODE BELOW !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// now let's calculate how we'd like the robot to move
	cmd_vel_eq(g_co2_sensor_0_ppm, g_co2_sensor_1_ppm, &desiredXVel, &desiredZVel);
	// !!!!!!!!!!!!!!!!! YOUR CODE ABOVE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	if (areWeStuck(g_x_coordinate, g_y_coordinate) && (ENABLE_ROBOT_STUCK_ACTION) && (desiredXVel > 0.1))
	{
		switch(state)
		{
			case 0: // turn right at 0 forward speed  
			{
				if (stateCounter < 1) 
				{
					stateCounter++; 
					base_cmd.linear.x = 0.0;
					base_cmd.angular.z = 1.0; 
				}
				else 
				{
					stateCounter=0;
					state=1; 
				}
				break; 
			}
			
			case 1: // try to move forward 
			{
				if (stateCounter < 1) 
				{
					stateCounter++; 
					base_cmd.linear.x = 1.0;
					base_cmd.angular.z = 0.0; 
				}
				else 
				{
					stateCounter=0;
					state=2; 
				}
				break; 
			}
			
			case 2: // backup and turn left 
			{
				if (stateCounter < 4) 
				{
					stateCounter++; 
					base_cmd.linear.x = -1.0;
					base_cmd.angular.z = -1.0; 
				}
				else 
				{
					stateCounter=0;
					state=3; 
				}
				break; 
			}
			
			case 3: // try to move forward 
			{
				if (stateCounter < 1) 
				{
					stateCounter++; 
					base_cmd.linear.x = 1.0;
					base_cmd.angular.z = 0.0; 
				}
				else 
				{
					stateCounter=0;
					state=0; 
				}
				break; 
			}
			
			default:
			{
				// do nothing 
			}
			
		}
	}
	
	else 
	{
	  base_cmd.linear.x = desiredXVel;
	  base_cmd.angular.z = desiredZVel; 
	}
		

	cmd_vel_pub_.publish(base_cmd); // tell the robot how we want it to move! 
	
	
	//we'll rely on our naptime call to control our CPU consumption 
	naptime.sleep(); 
  }

  //clean up when closing program 

  return 0; 
} 

