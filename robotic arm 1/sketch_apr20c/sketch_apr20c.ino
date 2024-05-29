/*
  SD card datalogger

  This example shows how to log data from three analog sensors
  to an SD card using the SD library.

  The circuit:
   analog sensors on analog ins 0, 1, and 2
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

  created  24 Nov 2010
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

*/

  #include <SPI.h>
  #include <SD.h>
  #include <Servo.h>
  #include <stdlib.h>
  #include <string.h>

  const int chipSelect = 4;
  const int R_button = 2;
  const int Clear_button =7;
  const int LED = 8;
  bool a=1,b=1,c=1;
//shoulder
  const int shoulder_rotate_MIN=0,shoulder_rotate_MAX=180;
  const int shoulder_swing_MIN=0,shoulder_swing_MAX=115;
//elbow
  const int elbow_swing_MIN=80,elbow_swing_MAX=180;
  const int elbow_rotate_MIN=0,elbow_rotate_MAX=180;
//wrist
  const int wrist_swing_MIN=0,wrist_swing_MAX=180;
  const int wrist_rotate_MIN=0,wrist_rotate_MAX=180;

  uint8_t delaytime =1;
  uint8_t runing_delaytime=10;

  char *token;
  int values[5];
  int first = 0;
  char *data;

  unsigned int countA0 =0,reffA0=0;
  unsigned int countA1 =0,reffA1=0;
  unsigned int countA2 =0,reffA2=0;
  unsigned int countA3 =0,reffA3=0;
  unsigned int countA4 =0,reffA4=0;
  unsigned int countA5 =0,reffA5=0;
  int angles[5];
  int count_1;

  

  Servo myservo1;
  Servo myservo2;
  Servo myservo3;
  Servo myservo4;
  Servo myservo5;


  String buffer;
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(R_button,INPUT_PULLUP);
  pinMode(Clear_button,INPUT_PULLUP);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,0);



  myservo1.detach();
  myservo2.detach();
  myservo3.detach(); 
  myservo4.detach();
  myservo5.detach(); 

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
      digitalWrite(LED,1);
    // don't do anything more:
    while (1);
  }  
  Serial.println("card initialized.");

  reffA0=countA0=map(analogRead(A0), 0, 1023, shoulder_rotate_MIN , shoulder_rotate_MAX);
  reffA1=countA1=map(analogRead(A1), 0, 1023, shoulder_swing_MIN, shoulder_swing_MAX);

  reffA2=countA2=map(analogRead(A2), 0, 1023, elbow_rotate_MIN , elbow_rotate_MAX);
  reffA3=countA3=map(analogRead(A3), 0, 1023, elbow_swing_MIN, elbow_swing_MAX);
  
  reffA4=countA4=map(analogRead(A4), 0, 1023, wrist_rotate_MIN , wrist_rotate_MAX);
  reffA5=countA5=map(analogRead(A5), 0, 1023, wrist_swing_MIN, wrist_swing_MAX);
Serial.print(reffA3);
//while(1);
 
 




 countA0=20;
 countA1=46;
 countA2=162;
 countA3=174;
 countA4=40;

  }

void loop() {

  myservo1.attach(3); 
  myservo2.attach(5);
  myservo3.attach(6); 
  myservo4.attach(9);
  myservo5.attach(10); 


  digitalWrite(LED,1);
  // make a string for assembling the data to log:
  String dataString = "";

  // read three sensors and append to the string:
  for (int analogPin = 0; analogPin < 5; analogPin++) {

    int sensor;
    if(analogPin==0){
     sensor = analogRead(analogPin);
     if(reffA0<map(sensor, 0, 1023, shoulder_rotate_MIN , shoulder_rotate_MAX)){
     countA0++;delay(delaytime);
     if(countA0>=shoulder_rotate_MAX)
     countA0--;}
     if(reffA0>map(sensor, 0, 1023, shoulder_rotate_MIN ,shoulder_rotate_MAX)){
     countA0--;delay(delaytime);
     if(countA0<=shoulder_rotate_MIN)
     countA0++;
     }
    dataString += String(countA0); 
     }

    if(analogPin==1){
         sensor = analogRead(analogPin);
     if(reffA1<map(sensor, 0, 1023, shoulder_swing_MIN, shoulder_swing_MAX)){
     countA1++;delay(delaytime);
     if(countA1>=shoulder_swing_MAX)
     countA1--;}
     if(reffA1>map(sensor, 0, 1023,shoulder_swing_MIN, shoulder_swing_MAX)){
     countA1--;delay(delaytime);
     if(countA1<=shoulder_swing_MIN)
     countA1++;
     }
    dataString += String(countA1); 
     }
  if(analogPin==2){
       sensor = analogRead(analogPin);
     if(reffA2<map(sensor, 0, 1023, elbow_rotate_MIN, elbow_rotate_MAX)){
     countA2++;delay(delaytime);
     if(countA2>=elbow_rotate_MAX)
     countA2--;}
     if(reffA2>map(sensor, 0, 1023, elbow_rotate_MIN, elbow_rotate_MAX)){
     countA2--;delay(delaytime);
     if(countA2<=elbow_rotate_MIN)
     countA2++;
     }
    dataString += String(countA2); 
     }
  if(analogPin==3){
       sensor = analogRead(analogPin);
     if(reffA3<map(sensor, 0, 1023, elbow_swing_MIN, elbow_swing_MAX)){
     countA3++;delay(delaytime);
     if(countA3>=elbow_swing_MAX)
     countA3--;}
     if(reffA3>map(sensor, 0, 1023, elbow_swing_MIN, elbow_swing_MAX)){
     countA3--;delay(delaytime);
     if(countA3<=elbow_swing_MIN)
     countA3++;
     }
    dataString += String(countA3); 
     }
  if(analogPin==4){
      sensor = analogRead(analogPin);
     if(reffA4<map(sensor, 0, 1023, wrist_rotate_MIN, wrist_rotate_MAX)){
     countA4++;delay(delaytime);
     if(countA4>=wrist_rotate_MAX)
     countA4--;}
     if(reffA4>map(sensor, 0, 1023, wrist_rotate_MIN, wrist_rotate_MAX)){
     countA4--;delay(delaytime);
     if(countA4<=wrist_rotate_MIN)
     countA4++;
     }
    dataString += String(countA4); 
     }


    // values[analogPin]=map(sensor, 0, 1023, 0, 180);
    // dataString += String(map(sensor, 0, 1023, 0, 180));
    if (analogPin < 4) {
      dataString += ",";
    }
  }
    
    
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  if(digitalRead(R_button)==1){
   digitalWrite(LED,0);
   delay(100);
  count_1=angles[0];
   Serial.print(count_1);
  }
  if(digitalRead(R_button)==0){
      digitalWrite(LED,0);
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
 
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
 dataFile.close();
       
char *token = strtok(const_cast<char*>(dataString.c_str()), ",");
      
      // Iterate through tokens and convert them to integers
      
      int i = 0;
      while (token != NULL && i < 5) {
        angles[i] = atoi(token);
        i++;
        token = strtok(NULL, ",");
      }
      
      // Control the servos with the extracted angles
      Serial.print("servo 1:");
      Serial.print(angles[1]);
      Serial.print("\t");
      Serial.print("servo 2:");
      Serial.print(angles[0]);
      Serial.print("\t");
      Serial.print("servo 3:");
      Serial.print(angles[2]);
      Serial.print("\t");
      Serial.print("servo 4:");
      Serial.print(angles[3]);
      Serial.print("\t");
      Serial.print("servo 5:");
      Serial.println(angles[4]);

      myservo1.write(angles[0]);
      while (a) {delay(1000);a=0;}
      myservo2.write(angles[1]);
         while (b) {delay(1000);b=0;}
      myservo3.write(angles[2]);
         while (c) {delay(1000);c=0;}
      myservo4.write(angles[3]);
     
      myservo5.write(angles[4]);

    // print to the serial port too:
   // Serial.println(dataString);



  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt while writing !");
      digitalWrite(LED,1);
  }

  }else{
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt");

  // if the file is available, write to it:
  if (dataFile) {
      while (dataFile.available()) {
      // Read data from the file
      String data = dataFile.readStringUntil('\n');
      
      // Split the string into tokens
      char *token = strtok(const_cast<char*>(data.c_str()), ",");
      
      // Iterate through tokens and convert them to integers
      int angles[5];
      int i = 0;
      while (token != NULL && i < 5) {
        angles[i] = atoi(token);
        i++;
        token = strtok(NULL, ",");
      }
      
      // Control the servos with the extracted angles
      // Control the servos with the extracted angles
      Serial.print("servo 1:");
      Serial.print(angles[0]);
      Serial.print("\t");
      Serial.print("servo 2:");
      Serial.print(angles[1]);
      Serial.print("\t");
      Serial.print("servo 3:");
      Serial.print(angles[3]);
      Serial.print("\t");
      Serial.print("servo 4:");
      Serial.print(angles[2]);
      Serial.print("\t");
      Serial.print("servo 5:");
      Serial.println(angles[4]);

      myservo1.write(angles[0]);
      myservo2.write(angles[1]);
      myservo3.write(angles[2]);
      myservo4.write(angles[3]);
      myservo5.write(angles[5]);
      delay(runing_delaytime);

    if(digitalRead(R_button)==0){
      break;
      while (digitalRead(R_button)==0); 
    }

    if(digitalRead(Clear_button)==0){
      SD.remove("datalog.txt");
      Serial.print("datalog.txt the file removed !");
      break;
      while(digitalRead(Clear_button)==0);
    }

    }

    
    dataFile.close();

  // if the file isn't open, pop up an error:
 } else {
    Serial.println("error opening datalog.txt while Reading !");
      digitalWrite(LED,1);
  }
  }

  if(digitalRead(Clear_button)==0){
    SD.remove("datalog.txt");
    Serial.print("datalog.txt the file removed !");
    while(digitalRead(Clear_button)==0);
  }


}










