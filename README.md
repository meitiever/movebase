# rpi3_movebase
this is part of code repository for my SLAM project.  
hardware part:  
consist of two arduino board.  
1. UNO - upload ros_control  
2. Mega 2560 - upload ros_sensor  
requirments:  
1. ros serial - https://github.com/ros-drivers/rosserial.  

rpi3 part:  
requirments:  
1. userland - for rpi 3 graphic card driver.  
2. apriltags_ros - for april tags tracking.  

best practice:  
1. Do not connect IMU to arduino. because the IMU module require a lot of resource and high speed connection. a lot of third party arduino and original arduino board unable to do it. i speed a lot of time on that.  
2. Do not buy an IMU module you do not know very well or try to understand IMU raw data or calibrate IMU youself unless you have time and a lot of money. this is a very good library for imu - https://github.com/richardstechnotes/RTIMULib2.git (it recommanded some affordable IMU chip and you can buy it from amazon or ebay)  
3. make you hardware as simple as possible, it is not worth to speed lots of time and money on it.  

