
int adc_key_in;
int key=-1;
int oldkey=-1;

int get_key(unsigned int input){
  int  adc_key_val[5] ={ 30, 150, 360, 535, 760 };
  int k;
  
  for (k = 0; k < 5; k++) {
    if (input < adc_key_val[k]) {
      return k;
    }
  }
  if (k >= 5)
    k = -1;
  return k;
}

void key_handler()
{
  adc_key_in = analogRead(7);
  digitalWrite(13,LOW); 
  key = get_key(adc_key_in);
 
  if (key != oldkey){
      delay(50);
      adc_key_in = analogRead(7);
      //Done("adc_key_in value = ", (String)adc_key_in);      
      key = get_key(adc_key_in);    // convert into key press
      if (key != oldkey) {
        oldkey = key;
          if (key >=0){
            digitalWrite(13,HIGH);
            switch(key){ // Serial.println(adc_key_in, DEC); Serial.println(msgs[2]); break;
              case 0: break;
              case 1: servo_s = stop_s; break;
              case 2: servo_s = default_s; break;
              case 3: turn_R(2, 0.6); break;
              case 4: turn_L(2, 0.3); break;
              case 5: stop(); break;
            }
          }
      }
  }
  delay(100);  
}

