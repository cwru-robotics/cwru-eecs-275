#! /bin/bash
##################################################################
### Created by Mike Gallagher, Case Western Reserve University ###
##################################################################
if [ "$1" == "orbbec" ]; 
then
echo "We see we have an orbbec camera"
else 
echo "We're assuming we have an asus camera"
fi

initialDirectory=$PWD
echo $initialDirectory

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
git clone https://github.com/tfoote/ros_astra_launch.git
# Need Orbbec code if we're not using Asus camera 
fi

mv $initialDirectory/minimal_turtlebot ~/ros_ws/src
mv $initialDirectory/cwru_deeplearning_robot/deeplearning_bringup ~/ros_ws/src

mv "$initialDirectory/cwru-turtlebot/turtleStart.sh" ~/ros_ws/src/deeplearning_bringup/launch

sudo chmod +755 "$initialDirectory/cwru-turtlebot/rc.local"
sudo mv "$initialDirectory/cwru-turtlebot/rc.local" /etc
sudo chmod +755 ~/ros_ws/src/deeplearning_bringup/launch/turtleStart.sh
sudo rm -r $initialDirectory/

source ~/ros_ws/devel/setup.bash 
cd ~/ros_ws
catkin_make


if [ "$1" == "orbbec" ]; 
then
echo "installing astra launch files"
~/ros_ws/src/ros_astra_camera/scripts/create_udev_rules
sudo mv ~/ros_ws/src/deeplearning_bringup/launch/deeplearning_orbbec.launch ~/ros_ws/src/deeplearning_bringup/launch/deeplearning.launch

# Need Astra code if we're not using Asus camera 
fi 
