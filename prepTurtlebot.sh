#! /bin/bash
##################################################################
### Created by Mike Gallagher, Case Western Reserve University ###
##################################################################
initialDirectory=$PWD

source /opt/ros/indigo/setup.bash

if [ -d "~/ros_ws/" ] 
then
    echo "ros_ws already exists, delete it and start over"
    sudo rm -r ~/ros_ws/src
else
    echo "ros_ws doesn't exist make a new one"
    mkdir -p ~/ros_ws/src
fi

cd ~/ros_ws/src
catkin_init_workspace

git clone https://github.com/yujinrobot/kobuki_msgs
#git clone https://github.com/orbbec/ros_astra_camera.git
# Need Orbbec code if we're not using Asus camera 

cd ~/ros_ws
catkin_make

mv $initialDirectory/cwru-eecs-275/minimal_turtlebot ~/ros_ws/src
mv $initialDirectory/cwru-eecs-275/cwru_deeplearning_robot/deeplearning_bringup ~/ros_ws/src

mv $initialDirectory/cwru-eecs-275/cwru-turtlebot/turtleStart.sh ~/ros_ws/src/deeplearning_bringup/launch

cd ~/ros_ws
catkin_make

#~/ros_ws/src/ros_astra_camera/scripts/create_udev_rules

sudo chmod +755 $initialDirectory/cwru-eecs-275/cwru-turtlebot/rc.local
sudo mv $initialDirectory/cwru-eecs-275/cwru-turtlebot/rc.local /etc
sudo chmod +755 /home/ubuntu/ros_ws/src/deeplearning_bringup/launch/turtleStart.sh
sudo rm -r $initialDirectory/cwru-eecs-275/
#sudo apt-get install ros-indigo-astra-launch
# Need Astra code if we're not using Asus camera 

