//Younghoon Choi
//COM 310 Final Robot

#include <SharpIR.h>
#include <Servo.h>
#include "SR04.h"

SharpIR lir = SharpIR(A4, 1080);
SharpIR rir = SharpIR(A5, 1080);

#define TRIG_PIN 13
#define ECHO_PIN 12


//Servos
//Upper
Servo RightBUpper;
Servo RightFUpper;
Servo LeftBUpper;
Servo LeftFUpper;

//Lower
Servo LeftBLower;
Servo RightBLower;
Servo LeftFLower;
Servo RightFLower;

//Ultrasonic sensor
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);

// variable to store the servo position
int pos;   

void setup() {
  Serial.begin(9600);
  RightBLower.attach(9);
  RightBUpper.attach(8);
  LeftBUpper.attach(7);
  LeftBLower.attach(6);
  RightFUpper.attach(5);
  LeftFUpper.attach(4);
  LeftFLower.attach(3);
  RightFLower.attach(2);
}

void loop() {
  long dis=sr04.Distance();

  int rdis = rir.distance();
  int ldis = lir.distance();

  Serial.println("left");
  Serial.println(ldis);
  
  Serial.println("right");
  Serial.println(rdis);
  
  objAvoid(dis, ldis, rdis);
}

//All the States of Dan

//Dan walks 
//Speed determines the pace of Dan
//Dan walks straight if both r and l are 0
//r is greater than 0, Dan turns right
//l is greater than 0, Dan turns left
void walk(int speed, int r, int l){
  for (pos = 5; pos <= 50; pos += 1) { 
    LeftBUpper.write(pos + (50-l));
    RightFUpper.write((135+r) - pos);

    LeftFUpper.write((100+l) - pos);
    RightBUpper.write((75-r) + pos);

    RightFLower.write((130+r)-pos);
    LeftBLower.write(pos + (65-l));
    delay(speed);                      
  }
   
  for (pos = 5; pos <= 50; pos += 1) { 
    LeftBUpper.write((115+l) - pos);
    RightFUpper.write((85-r) + pos);

    LeftFUpper.write(pos + (45-l));
    RightBUpper.write((130+r) - pos);

    LeftFLower.write(pos + (50-l));
    RightBLower.write((115+r) - pos);
    delay(speed);                      
  }
}

//Make Dan go up and down with his legs
void pushUp(){
  for (pos = 5; pos <= 55; pos += 1) { 
    LeftBUpper.write(50);
    RightBUpper.write(130);
    
    LeftFUpper.write(50);
    RightFUpper.write(130);

    LeftFLower.write(60+pos);
    RightBLower.write(130-pos);

    LeftBLower.write(50+pos);
    RightFLower.write(120-pos);
    
    delay(15);                      
  }
  for (pos = 5; pos <= 55; pos += 1) { 
    LeftBUpper.write(50);
    RightBUpper.write(130);
    
    LeftFUpper.write(50);
    RightFUpper.write(130);

    LeftFLower.write(120-pos);
    RightBLower.write(70 + pos);

    LeftBLower.write(105-pos);
    RightFLower.write(60+pos);
    
    delay(15);                      
  }
}

//Make Dan sit 
void sit(){
  LeftBUpper.write(90);
  RightBUpper.write(90);
    
  LeftFUpper.write(90);
  RightFUpper.write(90);

  LeftFLower.write(90);
  RightBLower.write(90);

  LeftBLower.write(90);
  RightFLower.write(90);
}


//Dan's Functions

//Object Avoidance
void objAvoid(int front, int left, int right){
  if (front < 10 && left < 5 && right < 5) {
    pushUp(); 
  }
  
  else if (left < 13){
    walk(10, 20, 0);
  }
  else if(right < 13) {
    walk(10, 0, 20);
  }
  else{
    walk(8,0,0);
  }
}
