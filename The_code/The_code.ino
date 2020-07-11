#include <Servo.h> //Arduino servo motor library

//configure the servo motors
Servo servo1;
Servo servo2;
Servo servo3;

const float pi = 3.1415926;
const float L1 = 5; // Length between the first motor and the second motor (in cm)
const float L2 = 8; // Length between the second motor and the third motor (in cm)
const float L3 = 4; // Length between the third motor and the end of arm (in cm)
float x; 
float y; 
float q1; // Angle of the first motor (in radian)
float q1_deg; // Angle of the first motor (in degree)
float q2; // Angle of the second motor (in radian)
float q2_deg; // Angle of the second motor (in degree)
float q3; // Angle of the second motor (in radian)
float q3_deg; // Angle of the second motor (in degree)
float q; // Sum of in radian (q1+q2+q3), it called theta
float q_deg; // Sum of in degree (q1_deg + q2_deg + q3_deg)
float x_1;
float x_2;
float x_3;
float y_1;
float y_2;
float y_3;
float k1;
float k2;
float x_inv;
float y_inv;
float x_sq ; // X square
float y_sq ; // // Y square
float L1_sq ; // L1 square
float L2_sq ; // L2 square
const int btn1 = 6;
const int btn2 = 7;
int btn1value = LOW; // For forward kinematics
int btn2value = LOW; // For inverse kinematics


void setup() {
  
servo1.attach(2);
servo2.attach(3);
servo3.attach(4);

pinMode (btn1 ,INPUT);
pinMode (btn2 ,INPUT);

Serial.begin(9600); 

}

void loop() {
  

btn1value = digitalRead(btn1);
btn1value = digitalRead(btn2);

if (btn1value == HIGH) // if button 1 is pressed (case of forward kinematic)
{
  //assume the values of the angles
  q1_deg = 50; 
  q2_deg = 30;
  q3_deg = 25;
  q_deg = q1_deg + q2_deg + q3_deg;
  
  q1 = q1_deg*pi/180;// convert the angle from degree to radian
  q2 = q2_deg*pi/180;// convert the angle from degree to radian
  q3 = q3_deg*pi/180;// convert the angle from degree to radian
  q = q_deg*pi/180; // convert the angle from degree to radian
  
  x_1 = L1*cos(q1);
  x_2= L2*cos(q1+q2);
  x_3 = L3*cos(q1+q2+q3);
  x = x_1 + x_2 + x_3; // The expected value with respect to X axis
  
  y_1 = L1*sin(q1);
  y_2 = L2*sin(q1+q2);
  y_3 = L3*sin(q1+q2+q3);
  y = y_1 + y_2 + y_3; // The expected value with respect to Y axis 
  
  servo1.write(q1_deg); 
  servo2.write(q2_deg);
  servo3.write(q3_deg); 
  
}

if (btn2value == HIGH) // if button 2 pressed (case of inverse kinematic)
{
  //assume the point on X and Y axes, and the value of theta
  x = 5; 
  y = 5; 
  q_deg = 140;
  q = q_deg*pi/180; // convert the angle from degree to radian
  
  x_inv = x - (L3*cos(q)); 
  y_inv = y - (L3*sin(q));
  
  x_sq = pow(x,2); 
  y_sq = pow(y,2); 
  L1_sq = pow(L1,2); 
  L2_sq = pow(L2,2); 
  
  q2 = acos((x_sq + y_sq - (L1_sq + L2_sq))/(2*L1*L2));
  k1 = (L1 + L2*cos(q2))*x_inv ;
  k2 = (L2*y_inv*sin(q2)) ;
  
  q1 = acos((k1 + k2)/(x_sq + y_sq)); 
  q3 = q - (q1 + q2) ; 
  
  q1_deg = q1*180/pi ; // convert the angle from radian to degree
  q2_deg = q2*180/pi; // convert the angle from radian to degree
  q3_deg = q3*180/pi; // convert the angle from radian to degree
  
  servo1.write(q1_deg); 
  servo2.write(q2_deg);
  servo3.write(q3_deg); 
  
}


}
