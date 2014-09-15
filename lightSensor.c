#include <SD.h>

int photoRPin = 0; 
int minLight;          //Used to calibrate the readings
int maxLight;          //Used to calibrate the readings
int lightLevel;
int adjustedLightLevel;

float runavg = 0;

long myIndex = 0;

const int samples=1000;

char light[10];

void setup() {
 Serial.begin(9600);
 
 Serial.print("Initializing SD card...");
 pinMode(8, OUTPUT);
 pinMode(10, OUTPUT);
 
 //Setup the starting light level limits
 lightLevel=analogRead(photoRPin);
 minLight=lightLevel-20;
 maxLight=lightLevel;
 
   if (!SD.begin(8)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

void loop(){
  
  long sumofsamples = 0;  
  String dataString = "";
  
  for(int i=0; i<samples; i++){
   
     //auto-adjust the minimum and maximum limits in real time
     lightLevel=analogRead(photoRPin);
     
     if(minLight>lightLevel) {
       minLight=lightLevel;
     }
     if(maxLight<lightLevel) {
       maxLight=lightLevel;
     }
     
      //Adjust the light level to produce a result between 0 and 100.
     adjustedLightLevel = map(lightLevel, minLight, maxLight, 0, 100);
    
     sumofsamples += adjustedLightLevel;
  }
 
 myIndex++;
 
 runavg = sqrt(sumofsamples/samples);
 dtostrf(runavg, 1, 2, light);

  dataString += String(light);
  dataString += ","; 
  dataString += myIndex;
  dataString += "\n";
 
 //Send the adjusted Light level result to Serial port (processing)
 Serial.println(adjustedLightLevel);

 File dataFile = SD.open("datalog.csv", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  } 
 
 //slow down the transmission for effective Serial communication.
 delay(50);
 
}