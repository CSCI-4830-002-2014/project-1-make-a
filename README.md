# Due 9/14/2014  (50 points)


## Name
Marc Simpson

## Hardware Photo (7 points)
![image](http://i.imgur.com/biffjDs.jpg)

## Data type (2 points) 

csv

## How did you get your prototype working? (7 points)

I just used the same code because I wanted to check the highest levels it could get to.

## Arduino Code (10 points)

#include <SD.h>

#define mic A0

const int silent = 343;
const int samples = 10000;
const int chipSelect = 8;

int led = 13;
int volume;
float runavg = 0;
long newSample;
long myIndex = 0;
char sound[10];


void setup() {                
  Serial.begin(9600); // For debugging

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
    volume = analogRead(mic); // Should read about 1.65V or 340(ish)
    newSample = volume - silent;
    newSample *= newSample;
    sumofsamples += newSample;  
  }

  myIndex++;
  runavg = sqrt(sumofsamples/samples);
  dtostrf(runavg, 1, 2, sound);

  dataString += String(sound);
  dataString += ","; 
  dataString += myIndex;
  dataString += "\n";

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

}

## Data Sample (7 points)
![image](http://i.imgur.com/rFmveED.png)

## How did you collect this data? (5 points)
I put the sensor in one room to measure what the highest levels would be.

## What signal do you think is in your data? (3 points)
What the highest noise levels in a room can be on a typical weekend (Thursday-Sunday morning)

## How fun was this mini-project? (3 points)
8

## How hard was it? (3 points)
5

## How much did you learn from the experience? (3 points)
8
