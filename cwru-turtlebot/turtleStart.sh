#! /bin/bash
ip=$(ip -f inet -o addr show wlan1|cut -d\  -f 7 | cut -d/ -f 1)
echo $ip
echo "We tried to start minimal launch"
source /home/ubuntu/ros_ws/devel/setup.bash
export ROS_IP=$ip
export ROS_MASTER_URI=http://$ip:11311
roslaunch deeplearning_bringup deeplearning.launch

