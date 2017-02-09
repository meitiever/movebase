int E1 = 5;     //定义M1使能端
int E2 = 6;     //定义M2使能端
int M1 = 4;    //定义M1控制端
int M2 = 7;    //定义M1控制端

float max_speed = 1.2; //should be max speed in m/s 
float min_right = 0.1; //should be min speed in m/s 
float min_left = 0.1;  //should be min speed in m/s 

int max_pluse = 255;
int min_right_p = 110;
int min_left_p = 120;

void stop(void){   //停止
  roboclaw.ForwardM1(address,0); //start Motor1 forward at half speed
  roboclaw.ForwardM2(address,0); //start Motor2 backward at half speed
  //digitalWrite(E1,LOW);
  //digitalWrite(E2,LOW);
}

void test(int a,int b){           
  roboclaw.ForwardM2(address,64); //start Motor2 backward at half speed
  //analogWrite (E2,b);
  //digitalWrite(M2,HIGH);
}

void advance(int a, int b) {
  roboclaw.ForwardM1(address,a); //start Motor1 forward at half speed
  roboclaw.BackwardM2(address,b); //start Motor2 backward at half speed
}

void advance(float speed) {

  if(speed > max_speed) speed = max_speed;
  if(speed < min_left) speed = min_left;
  int left = (int)( (speed - min_left)/ ((max_speed - min_left) / (max_pluse - min_left_p))) + min_left_p;
  int right = (int)( (speed - min_right) / (( max_speed - min_right) / (max_pluse - min_right_p))) + min_right_p;

  roboclaw.ForwardM1(address,left); //start Motor1 forward at half speed
  roboclaw.ForwardM2(address,right); //start Motor2 backward at half speed
}

void back_off (float speed) { //后退

  if(speed > max_speed) speed = max_speed;
  if(speed < min_left) speed = min_left;
  int left = (int)( (speed - min_left)/ ((max_speed - min_left) / (max_pluse - min_left_p))) + min_left_p;
  int right = (int)( (speed - min_right) / (( max_speed - min_right) / (max_pluse - min_right_p))) + min_right_p;

  roboclaw.BackwardM1(address,left); //start Motor1 forward at half speed
  roboclaw.BackwardM2(address,right); //start Motor2 backward at half speed
}

void turn_L (float a, float speed) { //左转

  if(speed > max_speed) speed = max_speed;
  if(speed < min_left) speed = min_left;
  int left = (int)( (speed - min_left) / ( (max_speed - min_left) / (max_pluse - min_left_p))) + min_left_p;  
  float as = 57.295 * a * 0.19;
  float right_new = as + speed;
  if(right_new > max_speed) right_new = max_speed - min_right;
  int right = (int)(right_new / ( ( max_speed - min_right) / (max_pluse - min_right_p))) + min_right_p;

  roboclaw.ForwardM1(address,left); //start Motor1 forward at half speed
  roboclaw.ForwardM2(address,right); //start Motor2 backward at half speed
  
  //analogWrite (E1,right);
  //digitalWrite(M1,HIGH);
  //analogWrite (E2,left);    
  //digitalWrite(M2,HIGH);
}

void turn_R (float a, float speed) { //右转

  if(speed > max_speed) speed = max_speed;
  if(speed < min_left) speed = min_left;
  int right = (int)( (speed - min_right) / ( (max_speed - min_right) / (max_pluse - min_right_p))) + min_right_p;
  float as = 57.295 * a * 0.19;
  float left_new = as + speed;
  if(left_new > max_speed) left_new = max_speed - min_left;
  int left = (int)(left_new / ( ( max_speed - min_left) / (max_pluse - min_left_p))) + min_left_p;

  roboclaw.ForwardM1(address,left); //start Motor1 forward at half speed
  roboclaw.ForwardM2(address,right); //start Motor2 backward at half speed
  //analogWrite (E1,right);
  //digitalWrite(M1,HIGH);
  //analogWrite (E2,left);
  //digitalWrite(M2,HIGH);
}

