
void processIMU() {
  sixDOF.getValues(angles);
  sixDOF.getYawPitchRoll(ypr);
  //temperature = bmp085GetTemperature(bmp085ReadUT());
  //pressure = bmp085GetPressure(bmp085ReadUP());

  String space = " ";
  String out = String(angles[0]*9.8, 2) + space + String(angles[1]*9.8, 2) + space + String(angles[2]*9.8 + 2.2, 2) + space + String(angles[3]*M_PI/180, 2) + space + String(angles[4]*M_PI/180, 2) + space + String(angles[5]*M_PI/180, 2) + space + String(ypr[0]*M_PI/180, 2)+ space + String(ypr[1]*M_PI/180, 2)+ space + String(ypr[2]*M_PI/180, 2);
  int len = 150;
  char buff[len];
  out.toCharArray(buff, len);
  Imu.data = buff;
}

