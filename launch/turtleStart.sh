#! /bin/bash
ip=$(ip -f inet -o addr show wlan1|cut -d\  -f 7 | cut -d/ -f 1)
echo $ip
echo "We tried to start minimal launch"
source /home/ubuntu/jetsonbot/devel/setup.bash
export ROS_MASTER_URI=http://$ip:11311
roslaunch turtlebot_bringup minimal.launch

