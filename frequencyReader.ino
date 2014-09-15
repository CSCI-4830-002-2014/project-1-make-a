#include <SD.h>
#include "pitches.h"

#define mic A0

const int chipSelect = 8;
const int samples = 1000;
const int silent = 343;

int sensorReading;
long myIndex = 0;
float readingAvg = 0;
char thisPitchString[10];
char readingAvgString[10];
int newSample;

void setup() {
  // initialize serial communications (for debugging only):
  Serial.begin(9600);
  
  Serial.print("Initializing SD card...");
  pinMode(chipSelect, OUTPUT);
  pinMode(10, OUTPUT);
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");  

}

void loop() {
  
  long sumofsamples = 0;  
  String dataString = "";

  for (int i=0; i<samples; i++){
    // read the sensor:
    sensorReading = analogRead(mic); // Should read about 1.65V or 340(ish)
    newSample = sensorReading - silent;
    newSample *= newSample;
    sumofsamples += newSample;  
  }
  
  myIndex++;
  readingAvg = sqrt(sumofsamples/samples);
  dtostrf(readingAvg, 1, 2, readingAvgString);
  
  // map the analog input range (in this case, 400 - 1000 from the photoresistor)
  // to the output pitch range (120 - 1500Hz)
  // change the minimum and maximum input numbers below
  // depending on the range your sensor's giving:
  //int thisPitch = map(sensorReading, 400, 1000, 120, 1500);
  int thisPitch = map(readingAvg, 0, 40, 120, 1500);
  dtostrf(thisPitch, 1, 2, thisPitchString);
  
  dataString += String(readingAvgString);
  dataString += ","; 
  dataString += String(thisPitchString);
  dataString += ","; 
  dataString += myIndex;
  dataString += "\n";
  
  File dataFile = SD.open("datalog.csv", FILE_WRITE);

  if (dataFile) {
    // if the file is available, write to it:
    dataFile.println(dataString);
    dataFile.close();
    
    // print sensor reading (so we know range) and calculated pitch to the serial port too:
    Serial.println(dataString);
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.csv");
  } 
  
}






