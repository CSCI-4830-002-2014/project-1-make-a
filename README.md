# Name
Daniel Nolan

# Hardware Photo
[insert a photo of your hardware]

# Data type
My data is saved through .csv

# How did you get your prototype working?
I followed the instructions given by the TA on tuesday and soldered what needed to be soldered. I used the implemented code that my TA gave me and uploaded it through Arduino. Then, I followed the Prokect 1 Make A portion online to test out my microphone which began recording sound pitches and outputting data when testing.

# Arduino Code
*/#include <SD.h>

#define mic A0

const int silent = 343;
const int samples = 10000;
const int chipSelect = 4;

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
  // if the file isnt open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  } 
  
}
*/
# Data Sample
[Replace the sample data file in this repo with your data file, then put the name of your file here]

# How did you collect this data?
In the Arduino program (after I plugged in the Arduino to my computer) 

# What signal do you think is in your data?
After subtracting the average DC offset of the signal (3.3/2 V), you would use the AnalogRead values for your data since the DC offset is the amount of static noise from the arduino. Then this value is squared to make sure it is the most accurate positive value and that it changes and depends on the amplitude.

# How fun was this mini-project? 
7

# How hard was it? 
3

# How much did you learn from the experience?
4
