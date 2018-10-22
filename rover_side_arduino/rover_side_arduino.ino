/*
   BYJ48 Stepper motor code
   Connect :
   IN1 >> D8
   IN2 >> D9
   IN3 >> D10
   IN4 >> D11
   VCC ... 5V Prefer to use external 5V Source
   Gnd
   written By :Mohannad Rawashdeh
  https://www.instructables.com/member/Mohannad+Rawashdeh/
     28/9/2013
  */

#define IN1  9
#define IN2  10
#define IN3  11
#define IN4  12
#define IN11  5
#define IN12  6
#define IN13  7
#define IN14  8

int Steps = 0;
int Steps2 = 0;
boolean Direction = true;// gre
boolean Direction2 = true;// gre
unsigned long last_time;
unsigned long last_time_tilt;
unsigned long currentMillis ;
unsigned long currentMillis_tilt ;
int steps=0;
int steps_tilt=0;

long time;
long time2;

void setup()
{
Serial.begin(9600);
pinMode(IN1, OUTPUT); 
pinMode(IN2, OUTPUT); 
pinMode(IN3, OUTPUT); 
pinMode(IN4, OUTPUT); 
pinMode(IN11, OUTPUT); 
pinMode(IN12, OUTPUT); 
pinMode(IN13, OUTPUT); 
pinMode(IN14, OUTPUT); 
// delay(1000);

}


String str, str_redd;
char str2[20];
char chr;
bool displayed=true;
String pan, tilt,forward, side;
int pan_processed;
int tilt_processed;
int forward_processed;
int side_processed;
int button_left;
int button_right;



void loop()
{
 //Serial.println("LOOP");
if(Serial.available()>0) {
    chr=Serial.read();
    while(chr!='\n'){
      displayed=true;
      if(Serial.available()>0) {
      str=str+chr;
      chr=Serial.read();
      }
      displayed=false;
    }
  }
  
  if(displayed==false){
    str_redd=str;
      str="";
      displayed=true;
    }
//Serial.println(str);
String str_sub;
char temp_arr[4];
str_sub=str_redd.substring(0,3);
str_sub.toCharArray(temp_arr, sizeof(temp_arr));
forward_processed=atoi(temp_arr);
str_sub=str_redd.substring(4,7);
str_sub.toCharArray(temp_arr, sizeof(temp_arr));
side_processed=atoi(temp_arr);
str_sub=str_redd.substring(8,11);
str_sub.toCharArray(temp_arr, sizeof(temp_arr));
pan_processed=atoi(temp_arr);
str_sub=str_redd.substring(12,15);
str_sub.toCharArray(temp_arr, sizeof(temp_arr));
tilt_processed=atoi(temp_arr);

//sscanf(str2, "%d,%d,%d,%d,%d,%d", forward_processed, side_processed, pan_processed, tilt_processed, button_left, button_right);


forward_processed=forward_processed-100;
side_processed=-(side_processed-100);
pan_processed=pan_processed-100;
tilt_processed=-(tilt_processed-100);

  
if(pan_processed<5&&pan_processed>-5){
  pan_processed = 0;
   digitalWrite(IN1, LOW);
   digitalWrite(IN2, LOW);
   digitalWrite(IN3, LOW);
   digitalWrite(IN4, LOW);
}
if(tilt_processed<5&&tilt_processed>-5){
  tilt_processed = 0;
   digitalWrite(IN11, LOW);
   digitalWrite(IN12, LOW);
   digitalWrite(IN13, LOW);
   digitalWrite(IN14, LOW);
}
//Serial.println(pan_processed);
//Serial.println(tilt_processed);

  currentMillis = millis();
  if(currentMillis-last_time>=(1+abs(100-abs(pan_processed)))){  
  if(pan_processed>0&&steps>=-2045){
    Direction=true;
    steps--;
    stepper(1);
  }else{
      if(pan_processed<0&&steps<=2045&&pan_processed){
        Direction=false;
        steps++;
        stepper(1);
      }
    }
  time=time+millis()-last_time;
  last_time=millis();
  }
//delay(abs(100-abs(pan_processed)));

  currentMillis_tilt = millis();
  if(currentMillis_tilt-last_time_tilt>=(1+abs(100-abs(tilt_processed)))){  
  if(tilt_processed>0&&steps_tilt>=-2045){
    Direction2=true;
    steps_tilt--;
    stepper2(1);
  }else{
      if(tilt_processed<0&&steps_tilt<=2045&&tilt_processed){
        Direction2=false;
        steps_tilt++;
        stepper2(1);
      }
    }
  time2=time2+millis()-last_time_tilt;
  last_time_tilt=millis();
  }
//delay(abs(100-abs(tilt_processed)));
}
    


void stepper(int xw){
  for (int x=0;x<xw;x++){
switch(Steps){
   case 0:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
   break; 
   case 1:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, HIGH);
   break; 
   case 2:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
   break; 
   case 3:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
   break; 
   case 4:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
   case 5:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
     case 6:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
   case 7:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
   break; 
   default:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
}
SetDirection();
}
} 
void SetDirection(){
if(Direction==1){ Steps++;}
if(Direction==0){ Steps--; }
if(Steps>7){Steps=0;}
if(Steps<0){Steps=7; }
}



void stepper2(int xw){
  for (int x=0;x<xw;x++){
switch(Steps2){
   case 0:
     digitalWrite(IN11, LOW); 
     digitalWrite(IN12, LOW);
     digitalWrite(IN13, LOW);
     digitalWrite(IN14, HIGH);
   break; 
   case 1:
     digitalWrite(IN11, LOW); 
     digitalWrite(IN12, LOW);
     digitalWrite(IN13, HIGH);
     digitalWrite(IN14, HIGH);
   break; 
   case 2:
     digitalWrite(IN11, LOW); 
     digitalWrite(IN12, LOW);
     digitalWrite(IN13, HIGH);
     digitalWrite(IN14, LOW);
   break; 
   case 3:
     digitalWrite(IN11, LOW); 
     digitalWrite(IN12, HIGH);
     digitalWrite(IN13, HIGH);
     digitalWrite(IN14, LOW);
   break; 
   case 4:
     digitalWrite(IN11, LOW); 
     digitalWrite(IN12, HIGH);
     digitalWrite(IN13, LOW);
     digitalWrite(IN14, LOW);
   break; 
   case 5:
     digitalWrite(IN11, HIGH); 
     digitalWrite(IN12, HIGH);
     digitalWrite(IN13, LOW);
     digitalWrite(IN14, LOW);
   break; 
     case 6:
     digitalWrite(IN11, HIGH); 
     digitalWrite(IN12, LOW);
     digitalWrite(IN13, LOW);
     digitalWrite(IN14, LOW);
   break; 
   case 7:
     digitalWrite(IN11, HIGH); 
     digitalWrite(IN12, LOW);
     digitalWrite(IN13, LOW);
     digitalWrite(IN14, HIGH);
   break; 
   default:
     digitalWrite(IN11, LOW); 
     digitalWrite(IN12, LOW);
     digitalWrite(IN13, LOW);
     digitalWrite(IN14, LOW);
   break; 
}
SetDirection2();
}
} 
void SetDirection2(){
if(Direction2==1){ Steps2++;}
if(Direction2==0){ Steps2--; }
if(Steps2>7){Steps2=0;}
if(Steps2<0){Steps2=7; }
}


