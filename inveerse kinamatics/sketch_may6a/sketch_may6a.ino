//#include <TrigApprox.h> // This is an example, you can use any trigonometric approximation library
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
Servo myservo1;
// Define the lengths of the robotic arm links
const float len1 = 12; // Length of the first link
const float len2 = 12; // Length of the second link

// Define the angles of the servo motors
int servo1Angle = 90; // Angle of servo motor 1 (base)
int servo2Angle = 90; // Angle of servo motor 2 (shoulder)

    float targetX = 12; // Example target X position
  float targetY = 12;

void setup() {
  Serial.begin(9600);
   myservo.attach(9);
  myservo1.attach(10);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
    pinMode(5,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);
  // Initialize servo motors
  // Add your servo initialization code here
 // Example target Y position
}

void loop() {
  // Get target position (x, y) from sensors, inputs, or calculations


  // Calculate inverse kinematics to determine servo angles
  calculateIK(targetX,targetY);
  Serial.print("[");
  Serial.print(targetX);
  Serial.print(",");
  Serial.print(targetY);
   Serial.print("]");
   Serial.println("");


if(digitalRead(3)==0){
targetX++;
delay(100);
if(targetX>=20)
targetX=20;
}

if(digitalRead(4)==0){
targetX--;
delay(100);
if(targetX==10)
targetX=10;
}



if(digitalRead(5)==0){
targetY++;
delay(100);
if(targetY>=20)
targetY=20;
}

if(digitalRead(6)==0){
targetY--;
delay(100);
if(targetY==10)
targetY=10;
}
  // Set servo angles accordingly
  // Add your servo control code here
}

void calculateIK(float x, float y) {
  // Calculate distance from base to end effector
  float dist = sqrt(x*x + y*y);

  // Check if the target point is within reach
  if (dist <= len1 + len2) {
    // Calculate angle1 (angle between link1 and the line from base to end effector)
    float angle1 = atan2(y, x);
  
    // Calculate angle2 (angle between link2 and the line from link1 to end effector)
    float cosAngle2 = (len1*len1 + len2*len2 - x*x - y*y) / (2*len1*len2);
    float sinAngle2 = sqrt(1 - cosAngle2*cosAngle2); // Using trig identity cos^2(theta) + sin^2(theta) = 1
    float angle2 = atan2(sinAngle2, cosAngle2);
  
    // Calculate servo angles
    servo1Angle = degrees(angle1);
    servo2Angle = degrees(angle1 + angle2);
    servo2Angle+=15;
    Serial.print(servo1Angle);
    Serial.print(",");
    Serial.print(servo2Angle);
    Serial.print("///////"); 
    myservo.write(servo1Angle);   
    myservo1.write(servo2Angle);   
  }
  // If the target point is out of reach, keep the servos at their previous angles
}