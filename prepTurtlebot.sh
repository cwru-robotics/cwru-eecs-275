#! /bin/bash
##################################################################
### Created by Mike Gallagher, Case Western Reserve University ###
##################################################################
if [ "$1" == "orbbec" ]; 
then
echo "We see we have an orbbec camera"
sudo apt-get install libudev-dev
#install udev lib
else 
echo "We're assuming we have an asus camera"
fi

initialDirectory=$PWD
echo $initialDirectory

source /opt/ros/indigo/setup.bash

echo "First try to remove ros_ws"
sudo rm -r /home/ubuntu/ros_ws/
mkdir -p /home/ubuntu/ros_ws/src

cd /home/ubuntu/ros_ws/src
catkin_init_workspace

git clone https://github.com/yujinrobot/kobuki_msgs
if [ "$1" == "orbbec" ]; 
then 
echo "cloning orbbec astra code"
git clone https://github.com/orbbec/ros_astra_camera.git
git clone https://github.com/orbbec/ros_astra_launch.git

source /home/ubuntu/ros_ws/devel/setup.bash 
cd /home/ubuntu/ros_ws
catkin_make --pkg astra_camera -DFILTER=OFF
# Let's force the filter to be off, should be by default but let's build here just to be sure
cd /home/ubuntu/ros_ws/src
fi

mv $initialDirectory/minimal_turtlebot /home/ubuntu/ros_ws/src
mv $initialDirectory/cwru_deeplearning_robot/deeplearning_bringup /home/ubuntu/ros_ws/src

mv "$initialDirectory/cwru-turtlebot/turtleStart.sh" /home/ubuntu/ros_ws/src/deeplearning_bringup/launch

sudo chmod +755 "$initialDirectory/cwru-turtlebot/rc.local"
sudo mv "$initialDirectory/cwru-turtlebot/rc.local" /etc
sudo chmod +755 /home/ubuntu/ros_ws/src/deeplearning_bringup/launch/turtleStart.sh
sudo rm -r $initialDirectory/

cd /home/ubuntu/ros_ws
catkin_make # call this first to complete ws initialization

source /home/ubuntu/ros_ws/devel/setup.bash 
cd /home/ubuntu/ros_ws
catkin_make


if [ "$1" == "orbbec" ]; 
then
echo "installing astra launch files"
/home/ubuntu/ros_ws/src/ros_astra_camera/scripts/create_udev_rules
sudo mv /home/ubuntu/ros_ws/src/deeplearning_bringup/launch/deeplearning_orbbec.launch /home/ubuntu/ros_ws/src/deeplearning_bringup/launch/deeplearning.launch

# Need Astra code if we're not using Asus camera 
fi 
