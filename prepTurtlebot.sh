#! /bin/bash
##################################################################
### Created by Mike Gallagher, Case Western Reserve University ###
##################################################################
if [ "$1" == "orbbec" ]; 
then
ehco "We see we have an orbbec camera"
else 
echo "We're assuming we have an asus camera"
fi

initialDirectory=$PWD

source /opt/ros/indigo/setup.bash

echo "First try to remove ros_ws"
sudo rm -r ~/ros_ws/
mkdir -p ~/ros_ws/src

cd ~/ros_ws/src
catkin_init_workspace

git clone https://github.com/yujinrobot/kobuki_msgs
if [ "$1" == "orbbec" ]; 
then 
echo "cloning orbbec astra code"
git clone https://github.com/orbbec/ros_astra_camera.git
# Need Orbbec code if we're not using Asus camera 
fi

cd ~/ros_ws
catkin_make

mv $initialDirectory/minimal_turtlebot ~/ros_ws/src
mv $initialDirectory/cwru_deeplearning_robot/deeplearning_bringup ~/ros_ws/src

mv $initialDirectory/cwru-turtlebot/turtleStart.sh ~/ros_ws/src/deeplearning_bringup/launch

cd ~/ros_ws
catkin_make

#~/ros_ws/src/ros_astra_camera/scripts/create_udev_rules

sudo chmod +755 $initialDirectory/cwru-turtlebot/rc.local
sudo mv $initialDirectory/cwru-turtlebot/rc.local /etc
sudo chmod +755 ~/ros_ws/src/deeplearning_bringup/launch/turtleStart.sh
sudo rm -r $initialDirectory/
if [ "$1" == "orbbec" ]; 
then
echo "installing astra launch files"
sudo apt-get install ros-indigo-astra-launch
# Need Astra code if we're not using Asus camera 
fi 
