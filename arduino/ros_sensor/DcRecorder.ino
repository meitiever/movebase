//#define PinA_left 2
//#define PinA_right 3
//
//#define PinB_left 8
//#define PinB_right 9

void EncoderInit()
{  
  pinMode(2,INPUT);
  pinMode(8,INPUT);
  pinMode(3,INPUT); 
  pinMode(9,INPUT);

  attachInterrupt(digitalPinToInterrupt(2), Left, RISING);
  attachInterrupt(digitalPinToInterrupt(3), Right, RISING);
}

void wheelSpeed()
{
  detachInterrupt(digitalPinToInterrupt(2));
  detachInterrupt(digitalPinToInterrupt(3));

//  String space = " ";
  speed_timer = millis() - speed_timer;
//  float cnt1 = 66*3.1415*((float)count1/390)/speed_timer;
//  float cnt2 = 66*3.1415*((float)count2/390)/speed_timer;
//  String out = String(cnt1, 2) + space + String(cnt2, 2) + space + String(speed_timer, 1);
//  char buff[30];
//  out.toCharArray(buff, 30);
  float v1 =  66*3.1415*((float)count1/390)/speed_timer;
  float v2 =  66*3.1415*((float)count2/390)/speed_timer;
  vx  = (v1+v2)/2;
  vy  = 0;
  vth = (v1-v2)/0.19;
  
  double dt = (float)speed_timer/1000;
  double delta_x = (vx * cos(th) - vy * sin(th)) * dt;
  double delta_y = (vx * sin(th) + vy * cos(th)) * dt;
  double delta_th = vth * dt;

  x += delta_x;
  y += delta_y;
  th += delta_th;
  //ros::Time current_time = nh.now();
  
  String space = " ";
  String out = String(vx, 2) + space + String(vy, 2) + space + String(vth, 2) + space + String(x, 2) + space + String(y, 2) + space + String(th, 2);
  int len = 150;
  char buff[len];
  out.toCharArray(buff, len);
  Vel.data = buff;
    
  count1 = 0;
  count2 = 0;
  attachInterrupt(digitalPinToInterrupt(2), Left, RISING);
  attachInterrupt(digitalPinToInterrupt(3), Right, RISING);
  speed_timer = millis();
}

void Left()
{
  if((millis()-l_time)>5) 
    count1 += 1;
  l_time==millis();
}

void Right()
{  
  if((millis()-r_time)>5) 
    count2 += 1;
  r_time==millis();  
}
