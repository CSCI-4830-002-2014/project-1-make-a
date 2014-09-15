# Due 9/14/2014  (50 points)


## Name
Ian Ker-Seymer

## Hardware Photo (7 points)
[insert a photo of your hardware]

## Data type (2 points) 
.csv

## How did you get your prototype working? (7 points)
  - I made sure that I used port 8 on the Arduino.
  - I averaged less values to get a higher sample rate
  - I tweaked setup my environent so I could tail stream values through my terminal and send them through a TCP socket

## Arduino Code (10 points)
```
#include <SD.h>

#define mic A0

const int silent = 343;
const int samples = 5000;
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
```

## Data Sample (7 points)
datalog.csv

## How did you collect this data? (5 points)
I put my Arduino in the CSEL to collect sounds throughout the day.

## What signal do you think is in your data? (3 points)
I think I will be able to pull the rotation of classes and the general class schedule of CS students.
I think we will see growth in the morning and decay in the afternoon with ups and downs in between.

## How fun was this mini-project? (3 points)
8

## How hard was it? (3 points)
6

## How much did you learn from the experience? (3 points)
8
