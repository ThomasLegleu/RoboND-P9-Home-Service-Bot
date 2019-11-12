#!/bin/sh
xterm  -e  " source ~/catkin_ws5/devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch " &
sleep 3
xterm  -e  " source ~/catkin_ws5/devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch " &
sleep 3
xterm  -e  " source ~/catkin_ws5/devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 3
xterm  -e  " source ~/catkin_ws5/devel/setup.bash; rosrun pick_objects pick_objects  "