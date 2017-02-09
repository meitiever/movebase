#include <Wire.h>
#include <FreeSixIMU.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <HMC5883L.h>
#include <ros.h>
#include <std_msgs/String.h>
//#include <nav_msgs/Odometry.h>
//#include <geometry_msgs/TwistStamped.h>
//#include <sensor_msgs/Imu.h>
//#include "ros/time.h"

/*********************************************************************************/
std_msgs::String Imu;
//sensor_msgs::Imu Imu;
std_msgs::String Vel;
//nav_msgs::Odometry odom;

ros::Publisher pub_imu("IMU", &Imu);
ros::Publisher pub_vel("VEL", &Vel);
//ros::Publisher pub_vel("VEL", &odom);

ros::NodeHandle nh;

long publisher_timer;
long speed_timer;
/*********************************************************************************/

/*********************************************************************************/
float angles[6];
float ypr[3]; // yaw pitch roll
//float heading;
char frame_id[] = "IMU";

//float temperature = 0;
//float pressure = 0;
//float altitude = 0;

// Set the FreeSixIMU object
FreeSixIMU sixDOF = FreeSixIMU();

//HMC5883L compass;
// Record any errors that may occur in the compass.
//int error = 0;
/*********************************************************************************/

/*********************************************************************************/
int count1 = 0;
int count2 = 0;
float vx, vy, vth, x, y, th;
//tf::TransformBroadcaster odom_broadcaster;
unsigned long l_time = 0, r_time = 0;
/*********************************************************************************/

void setup() {
  Wire.begin();
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  //odom_broadcaster.init(nh);
  
  nh.advertise(pub_imu);
  nh.advertise(pub_vel);
  
  // Init Encoder
  EncoderInit();
  
  //init IMU
  sixDOF.init(); //init the Acc and Gyro
  //compass = HMC5883L(); // init HMC5883
  
  //error = compass.SetScale(1.3); // Set the scale of the compass.
  //error = compass.SetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous  
  //if(error != 0) // If there is an error, print it out.
  //  Serial.println(compass.GetErrorText(error));

  //bmp085Calibration(); // init barometric pressure sensor
}

void loop() {
  if(millis() > publisher_timer) {
    processIMU();    
    pub_imu.publish(&Imu);
    wheelSpeed();
    pub_vel.publish(&Vel);
    //pub_vel.publish(&odom);
    publisher_timer = millis() + 500;
    //printData();
  }
  //delay(200);
  nh.spinOnce();
}

