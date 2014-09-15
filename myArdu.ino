#include <SD.h>

#define mic A0

const int   silent = 343;
const int   samples = 10000;
const int   chipSelect = 8;
const char* date = "Friday Night, Sept. 12, 2014, 8:00pm\n";

int led = 13;
int volume;
float runavg = 0;
long newSample;
long myIndex = 0;
char sound[10];
unsigned long time;

void setup() { // used to initialize variables, pin modes, start using libraries, etc.
  // opens serial port, sets data rate to 9600 bps
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
  File dataFile = SD.open("datalog.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println(date);
    dataFile.close();
    Serial.println(date);
  }
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

  time = millis();
  myIndex++;
  runavg = sqrt(sumofsamples/samples);
  dtostrf(runavg, 1, 2, sound);

  dataString += String(sound);
  dataString += ",";
  dataString += myIndex;
  if (myIndex % 10 == 1) {
    dataString += ",------";
    time = time / 1000;
    dataString += time;
    dataString += " seconds------";
  }
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
