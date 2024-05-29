#include <Servo.h>

// Define servo pins
#define BASE_SERVO_PIN 9
#define SHOULDER_SERVO_PIN 10
#define ELBOW_SERVO_PIN 11

// Define servo objects
Servo baseServo;
Servo shoulderServo;
Servo elbowServo;

// Define arm dimensions (lengths of each segment)
float L1 = 7; // Base to shoulder
float L2 = 12; // Shoulder to elbow
float L3 = 12; // Elbow to end-effector

// Function to calculate inverse kinematics
void calculateIK(float x, float y, float z) {
  // Calculate angle for base servo
  float theta1 = atan2(y, x) * 180 / PI;
  baseServo.write(theta1);
 Serial.print("baseServo:");
Serial.print(theta1);
  // Calculate distance from base to end-effector projection on xy-plane
  float d = sqrt(x*x + y*y);

  // Calculate angle for shoulder servo using law of cosines
  float cosTheta2 = (L2*L2 + L3*L3 - d*d - z*z) / (2 * L2 * L3);
  float theta2 = acos(cosTheta2) * 180 / PI;
  shoulderServo.write(theta2-48);
Serial.print(" ,shoulderServo:");
Serial.print(theta2);

  // Calculate angle for elbow servo using law of cosines
  float cosTheta3 = ((L2*L2 + L3*L3 - d*d - z*z) / (2 * L2 * L3)) - ((z*(L2+L3*cosTheta2))/(L3*sin(theta2)));
  float theta3 = acos(cosTheta3) * 180 / PI;
  elbowServo.write(theta3);
  Serial.print(" ,elbowServo:");
  Serial.print(theta3 +72);
 Serial.println(" ");
}

void setup() {
   Serial.begin(9600);
  // Attach servos to pins

  baseServo.attach(BASE_SERVO_PIN);
  shoulderServo.attach(SHOULDER_SERVO_PIN);
  elbowServo.attach(ELBOW_SERVO_PIN);

  // Set initial position
 // calculateIK(20, 20, 20); // Example end-effector position
}

void loop() {
  // Your main code here
    calculateIK(12, 12, 0); // Example end-effector position
}