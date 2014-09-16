# Name
Daniel Nolan

# Hardware Photo
![My Ballin' Arduino!](http://imgur.com/AwsUR8a.png)

# Data type
My data is saved through .csv and is opened through Excel.

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
DATALOG.csv in repo

# How did you collect this data?
In the Arduino program (after I plugged in the Arduino to my computer). I used the Arduino program and set aside a sketch and tested out my code to get initial readings before actually implementing the SD card in my Arduino board with the code above in it. 

# What signal do you think is in your data?
After subtracting the average DC offset of the signal (3.3/2 V), you would use the AnalogRead values for your data since the DC offset is the amount of static noise from the arduino. Then this value is squared to make sure it is the most accurate positive value and that it changes and depends on the amplitude. My data is the square value of the wave amplitudes recorded by sound through my amplified microphone. This gives me only positive values so there are only peaks to easily measure the changing of amplitude due to possibly lower sounds in the area the Arduino is.

# How fun was this mini-project? 
7

# How hard was it? 
3

# How much did you learn from the experience?
4
