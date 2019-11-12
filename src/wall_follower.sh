
#!/bin/sh
export TURTLEBOT_3D_SENSOR=kinect
xterm  -e  "source ~/catkin_ws5/devel/setup.bash;  roslaunch turtlebot_gazebo turtlebot_world.launch " &
sleep 3
xterm  -e  " source ~/catkin_ws5/devel/setup.bash; roslaunch turtlebot_gazebo gmapping_demo.launch " &
sleep 3
xterm  -e  " source ~/catkin_ws5/devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 3
xterm  -e  " source ~/catkin_ws5/devel/setup.bash; rosrun wall_follower wall_follower  "