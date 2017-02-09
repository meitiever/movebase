int E1 = 5;     //定义M1使能端
int E2 = 6;     //定义M2使能端
int M1 = 4;    //定义M1控制端
int M2 = 7;    //定义M1控制端

float max_speed = 0.8; //should be max speed in m/s 
float min_right = 0.15; //should be min speed in m/s 
float min_left = 0.15;  //should be min speed in m/s 

int max_pluse = 255;
int min_right_p = 160;
int min_left_p = 160;

void stop(void){   //停止
  digitalWrite(E1,LOW);
  digitalWrite(E2,LOW);
}

void test(int a,int b){           
  analogWrite (E2,b);
  digitalWrite(M2,HIGH);
}

void advance(int a, int b) {
  analogWrite (E1,a);
  digitalWrite(M1,HIGH);
  analogWrite (E2,b);
  digitalWrite(M2,HIGH);
}

void advance(float speed) {

  if(speed > max_speed) speed = max_speed;
  if(speed < min_left) speed = min_left;
  int left = (int)( (speed - min_left)/ ((max_speed - min_left) / (max_pluse - min_left_p))) + min_left_p;
  int right = (int)( (speed - min_right) / (( max_speed - min_right) / (max_pluse - min_right_p))) + min_right_p;

  analogWrite (E1,right);
  digitalWrite(M1,HIGH);
  analogWrite (E2,left);
  digitalWrite(M2,HIGH);
}

void back_off (float speed) { //后退

  if(speed > max_speed) speed = max_speed;
  if(speed < min_left) speed = min_left;
  int left = (int)( (speed - min_left)/ ((max_speed - min_left) / (max_pluse - min_left_p))) + min_left_p;
  int right = (int)( (speed - min_right) / (( max_speed - min_right) / (max_pluse - min_right_p))) + min_right_p;

  analogWrite (E1,right);
  digitalWrite(M1,LOW);
  analogWrite (E2,left);
  digitalWrite(M2,LOW);
}

void turn_L (float a, float speed) { //左转

  if(speed > max_speed) speed = max_speed;
  if(speed < min_left) speed = min_left;
  float speed_right = a * 0.19/2 + speed;
  float speed_left = speed * 2 - speed_right;
  
  int right = (int)( (speed_right - min_right) / ( (max_speed - min_right) / (max_pluse - min_right_p))) + min_right_p;  
  if(speed_left > max_speed) speed_left = max_speed - min_left;
  int left = (int)(speed_left / ( ( max_speed - min_left) / (max_pluse - min_left_p))) + min_left_p;
    
  analogWrite (E1,right);
  digitalWrite(M1,HIGH);
  analogWrite (E2,left);
  digitalWrite(M2,HIGH);
}

void turn_R (float a, float speed) { //右转

  if(speed > max_speed) speed = max_speed;
  if(speed < min_left) speed = min_left;
  float speed_left = a * 0.19/2 + speed;
  float speed_right = speed * 2 - speed_left;
  
  int left = (int)( (speed_left - min_left) / ( (max_speed - min_left) / (max_pluse - min_left_p))) + min_left_p;  
  if(speed_right > max_speed) speed_right = max_speed - min_right;
  int right = (int)(speed_right / ( ( max_speed - min_right) / (max_pluse - min_right_p))) + min_right_p;
  
  analogWrite (E1,right);
  digitalWrite(M1,HIGH);
  analogWrite (E2,left);
  digitalWrite(M2,HIGH);
}

