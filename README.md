# Due 9/14/2014  (50 points)


## Name
Michael Aaron

## Hardware Photo (7 points)
![Ardiuno](./ard_1.jpeg)

## Data type (2 points) 
csv

## How did you get your prototype working? (7 points)
Substantial changes. drastically increased the sample rate, set a threshold to start sampeling values when I play
a chord (it took a long time to find a value that worked well), changed the loop so that it would automatically record the next 200 samples after a threshold is hit. Put in a sample index so it is easy for me to seperate notes when we get to evaluating data. Probably some other changes I forgot about. 

## Arduino Code (10 points)
#include <SoftwareSerial.h>

#include <SD.h>

#define mic A0

const int sampleSize= 200;
const int chipSelect = 8;
const int threshold = 40;

int silent = 340;
int led = 13;
int volume;
float runavg = 0;
long newSample;
long myIndex = 0;
long sample_index=0;
char sound[10];
int minIndex=5;

 
void setup() {                
  Serial.begin(9600); // For debugging
  
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
    
}
 
void loop() {
  
  
  String dataString = "";
  volume = analogRead(mic); // Should read about 1.65V or 340(ish)
  newSample = volume - silent;
  dtostrf(newSample, 1, 2, sound);

  if (int(newSample)>threshold)
  {
    sample_index++;
    while(myIndex<sampleSize){
      dataString = "";
      volume = analogRead(mic);
      newSample = volume - silent;
      dtostrf(newSample, 1, 2, sound);
      myIndex++;
      dataString += String(sound);
      dataString += " "; 
      dataString += sample_index;
      dataString += " ";
      dataString += myIndex;
      dataString += "\n";
      // if the file is available, write to it:
      File dataFile = SD.open("datalog.csv", FILE_WRITE);
      if (dataFile) {
        dataFile.println(dataString);
        // print to the serial port too:
        Serial.println(dataString);
        dataFile.close();
      }  
      // if the file isn't open, pop up an error:
      else {
        Serial.println("error opening datalog.txt");
        } 
    }
  }
  else{
    myIndex=0;
  }
  
}
## Data Sample (7 points)
make_1.ino

## How did you collect this data? (5 points)
Played single notes on a barritone ukulele, I need to work on how to delimit the notes, as well as figure out how to transform a voltage reading to something I can run FFT on, like a .wav file

## What signal do you think is in your data? (3 points)
I am hoping I can pull individual "note" voltage section, transform them with FFT, and compare against MIDI files to have a "best guess" for the played note.

## How fun was this mini-project? (3 points)
7

## How hard was it? (3 points)
6 (although to actually get the data I am looking for more like an 8)

## How much did you learn from the experience? (3 points)
7 - Awesome project, no real compaints! 