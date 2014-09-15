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
