# line to run docker from image:

docker run -it --net=host --env=DISPLAY --volume=$HOME/.Xauthority:/root/.Xauthority ros:foxy-ros-base
