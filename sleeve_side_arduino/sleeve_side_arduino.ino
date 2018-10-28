
#define button_left 2
#define button_right 3

void setup() {
 Serial.begin(9600);

pinMode(button_left, INPUT_PULLUP);
pinMode(button_right, INPUT_PULLUP);

}
char str[64];

void loop() {  
  int tilt_raw=analogRead(A0);
  int tilt_processed=map(tilt_raw, 0, 1023, 0, 200);
  if(tilt_processed<=5&&tilt_processed>=-5) tilt_processed=0;
  int pan_raw=analogRead(A1);
  int pan_processed=map(pan_raw, 0, 1023, 0, 200);
  if(pan_processed<=5&&pan_processed>=-5) pan_processed=0;
  int forward_raw=analogRead(A2);
  //int forward_processed=map(forward_raw, 0, 1023, 0, 200);
  //if(forward_processed<=5&&forward_processed>=-5) forward_raw=0;
  int side_raw=analogRead(A3);
  //int side_processed=map(side_raw, 0, 1023, 0, 200);
  //if(side_processed<=5&&side_processed>=-5) side_raw=0;
  int button_left_val=digitalRead(2);
  int button_right_val=digitalRead(3);
  sprintf(str, "%04d,%04d,%03d,%03d,%01d,%01d", side_raw,forward_raw,pan_processed,tilt_processed,button_left_val,button_right_val);
  Serial.println(str);
  delay(200);
}

