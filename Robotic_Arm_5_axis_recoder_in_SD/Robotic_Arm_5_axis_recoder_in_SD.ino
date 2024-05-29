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
  char *token;
  int values[5];
  int i = 0;
  char *data;

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

  myservo1.attach(3); 
  myservo2.attach(5);
  myservo3.attach(6); 
  myservo4.attach(9);
  myservo5.attach(10); 



  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
      digitalWrite(LED,1);
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
  }

void loop() {
  // make a string for assembling the data to log:
  String dataString = "";

  // read three sensors and append to the string:
  for (int analogPin = 0; analogPin < 5; analogPin++) {

    int sensor;
    if(analogPin==0){
     sensor = analogRead(analogPin);
    dataString += String(map(sensor, 0, 1023, 0, 180)); // shoulder rotate=0-180
     }
    if(analogPin==1){
     sensor = analogRead(analogPin);
    dataString += String(map(sensor, 0, 1023, 0, 115));//shoulder swing 0-115
     }
  if(analogPin==2){
     sensor = analogRead(analogPin);
    dataString += String(map(sensor, 0, 1023, 113,180));//elbow swing=180-113
     }
  if(analogPin==3){
     sensor = analogRead(analogPin);
    dataString += String(map(sensor, 0, 1023, 0, 180));//wrist swing 0-180
     }
  if(analogPin==4){
     sensor = analogRead(analogPin);
    dataString += String(map(sensor, 0, 1023, 0, 180));//wrist rotate 0-180
     }


    // values[analogPin]=map(sensor, 0, 1023, 0, 180);
    // dataString += String(map(sensor, 0, 1023, 0, 180));
    if (analogPin < 4) {
      dataString += ",";
    }
  }
    
    
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  
  if(digitalRead(R_button)==0){
      digitalWrite(LED,0);
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
 
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
 dataFile.close();
       
char *token = strtok(const_cast<char*>(dataString.c_str()), ",");
      
      // Iterate through tokens and convert them to integers
      int angles[5];
      int i = 0;
      while (token != NULL && i < 5) {
        angles[i] = atoi(token);
        i++;
        token = strtok(NULL, ",");
      }
      
      // Control the servos with the extracted angles
      Serial.print("servo 1:");
      Serial.print(angles[0]);
      Serial.print("\t");
      Serial.print("servo 2:");
      Serial.print(angles[1]);
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
      myservo2.write(angles[1]);
      myservo3.write(angles[2]);
      myservo4.write(angles[3]);
      myservo5.write(angles[5]);

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
      Serial.print(angles[2]);
      Serial.print("\t");
      Serial.print("servo 4:");
      Serial.print(angles[3]);
      Serial.print("\t");
      Serial.print("servo 5:");
      Serial.println(angles[4]);

      myservo1.write(angles[0]);
      myservo2.write(angles[1]);
      myservo3.write(angles[2]);
      myservo4.write(angles[3]);
      myservo5.write(angles[5]);


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









