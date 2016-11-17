#! /bin/bash

git clone https://github.com/cwru-robotics/cwru-eecs-275.git

initialDirectory=$PWD

source /opt/ros/indigo/setup.bash
mkdir -p ~/ros_ws/src

cd ~/ros_ws/src
catkin_init_workspace

git clone https://github.com/yujinrobot/kobuki_msgs
#git clone https://github.com/orbbec/ros_astra_camera.git

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
