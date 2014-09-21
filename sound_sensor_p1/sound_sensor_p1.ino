#include <SD.h>
#define lightsensor A0
const int darkness = 343;
const int samples = 10000;
const int chipSelect = 8;
int led = 13;
int exposure;
float runavg = 0;
long newSample;
long myIndex = 0;
char light[10];
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
Serial.println("card initialized. New data set:");  
}
void loop() {
long sumofsamples = 0;  
String dataString = "";
for (int i=0; i<samples; i++){
exposure = analogRead(lightsensor); // Should read about 1.65V or 340(ish)
newSample = exposure - darkness;
newSample *= newSample;
sumofsamples += newSample;  
}
myIndex++;
runavg = sqrt(sumofsamples/samples);
dtostrf(runavg, 1, 2, light);
dataString += String(light);
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
