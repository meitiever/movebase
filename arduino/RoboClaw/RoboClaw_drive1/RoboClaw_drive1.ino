
//See BareMinimum example for a list of library functions

//Includes required to use Roboclaw library
#include <SoftwareSerial.h>
#include "RoboClaw.h"

#include <Servo.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>
#include <geometry_msgs/Twist.h>

/*********************************************************************************/
Servo servo;  // create servo object to control a servo
int servoPin = 10;
int stop_s = 1500;
int default_s = 1490;
int servo_s = 0;
/*********************************************************************************/

/*********************************************************************************/
SoftwareSerial serial(0,1);  
RoboClaw roboclaw(&serial,10000);

#define address 0x80
/*********************************************************************************/

/*
tested on 164 155 with speed of 0.57m/s
*/

void dc_twist( const geometry_msgs::Twist& msg) {    
  if (msg.angular.z == 0 && msg.linear.x == 0)
  {
    stop();
  }
  else
  {
    if (msg.angular.z < 0)
    {
      turn_R(abs(msg.angular.z), abs(msg.linear.x));
    }
    else if (msg.angular.z > 0)
    {
      turn_L(abs(msg.angular.z), abs(msg.linear.x));
    }
    else if (msg.linear.x < 0)
    {      
      back_off(abs(msg.linear.x));
    }
    else if (msg.linear.x > 0)
    {
      advance(abs(msg.linear.x));
    }
  }
}

void servo_cb( const std_msgs::Int16& cmd_msg){
  servo_s = cmd_msg.data;
}

/*********************************************************************************/
//std_msgs::String Vel;
//ros::Publisher pub_vel("VEL", &Vel);

ros::Subscriber<std_msgs::Int16> sub_servo("servo", servo_cb);
//ros::Subscriber<std_msgs::String> sub_dc("dc", dc_cb);
ros::Subscriber<geometry_msgs::Twist> sub_dc_control("cmd_vel", dc_twist);

ros::NodeHandle nh;

long publisher_timer;
long speed_timer;
long last_run;
/*********************************************************************************/

/*********************************************************************************/
int count1 = 0;
int count2 = 0;
float vx, vy, vth, x, y, th;
unsigned long l_time = 0, r_time = 0;
/*********************************************************************************/

void setup() {  
  // Setup servo
  servo.attach(servoPin);  // attaches the servo on pin 9 to the servo object
  servo_s = stop_s;

  roboclaw.begin(38400);
  
  int i;
  for(i=6;i<=9;i++)
    pinMode(i, OUTPUT);

  nh.getHardware()->setBaud(115200);
  nh.initNode();
  
  nh.subscribe(sub_dc_control);
  nh.subscribe(sub_servo);

}

void loop() {
  
  if(millis() < last_run+500) {    
    delay(last_run+500-millis());
  }

  Scan(servo_s);
  nh.spinOnce();
  last_run=millis();
}

