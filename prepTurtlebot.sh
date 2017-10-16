
#! /bin/bash
##################################################################
### Created by Mike Gallagher, Case Western Reserve University ###
##################################################################
echo "We see we have a Kinect camera"
echo "Make sure usbcore.autosuspend=-1 is in /boot/extlinux/extlinux.conf"
echo "This shuts off autosuspend and makes Kinect reliable" 

sudo apt-get install ros-indigo-freenect-launch
sudo apt-get install ros-indigo-libfreenect

initialDirectory=$PWD
echo $initialDirectory

source /opt/ros/indigo/setup.bash

echo "First try to remove ros_ws"
sudo rm -r ~/ros_ws/
mkdir -p ~/ros_ws/src

cd ~/ros_ws/src
catkin_init_workspace

git clone https://github.com/yujinrobot/kobuki_msgs

mv $initialDirectory/minimal_turtlebot ~/ros_ws/src
mv $initialDirectory/cwru_deeplearning_robot/deeplearning_bringup ~/ros_ws/src
mv $initialDirectory/51-kinect.rules /etc/udev/rules.d


mv "$initialDirectory/cwru-turtlebot/turtleStart.sh" ~/ros_ws/src/deeplearning_bringup/launch

sudo chmod +755 "$initialDirectory/cwru-turtlebot/rc.local"
sudo mv "$initialDirectory/cwru-turtlebot/rc.local" /etc
sudo chmod +755 ~/ros_ws/src/deeplearning_bringup/launch/turtleStart.sh
sudo rm -r $initialDirectory/

cd ~/ros_ws
catkin_make # call this first to complete ws initialization

source ~/ros_ws/devel/setup.bash 
cd ~/ros_ws
catkin_make

