#include <SoftwareSerial.h>

#include <SD.h>

#define mic A0

const int silent = 343;
const int samples = 25;
const int chipSelect = 8;
const int threshold = 20;

int led = 13;
int volume;
float runavg = 0;
long newSample;
long myIndex = 0;
char sound[10];

 
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
  
  
  long sumofsamples = 0;  
  String dataString = "";
  
  for (int i=0; i<samples; i++){
    volume = analogRead(mic); // Should read about 1.65V or 340(ish)
    newSample = volume - silent;
    newSample *= newSample;
    sumofsamples += newSample;  
  }
  
  
  runavg = sqrt(sumofsamples/samples);
  dtostrf(runavg, 1, 2, sound);

  if (int(runavg)>threshold)
  {
    myIndex++;
    dataString += String(sound);
    dataString += ","; 
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
