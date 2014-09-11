#include <util/atomic.h>
#include <SD.h>

#define mic A0

int silent = 330; // Update with last average each loop
#define SAMPLES 10000
#define chipSelect 8

int led = 13;
long myIndex = 0;

// File
char filename[16]; // "soundXXXX.csv"

// Simple timer class
volatile uint32_t ovfcnt = 0;
uint32_t timer_st = 0;
ISR(TIMER1_OVF_vect) { ovfcnt++; }

class timer {
public:
  static void init() {
    cli();
    TCCR1A = 0x00; // Normal pin mode, normal counting
    // TCCR1B determines prescaler: 16MHz clock
    //                prescaler      tick    period     extended period (48 bits)   tics/ms
//  TCCR1B = 0x01; //         1    62.5ns    
//  TCCR1B = 0x02; //         8     0.5us    
    TCCR1B = 0x03; //        64       4us    0.2621ms    35 years                   250
//  TCCR1B = 0x05; //      1024      64us    4.1940s    570 years
    TIMSK1 = (1 << TOIE1); // Timer 1 overflow interrupt enabled
    ovfcnt = 0;
    TCNT1  = 0;
    sei();
  }
  static void reset() {
    ovfcnt = 0;
    TCNT1 = 1;
  }
  // Number of hundredth of a second since last reset
  static uint32_t hs() { 
    uint16_t tl;
    uint64_t th;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
      tl = TCNT1;
      th = ovfcnt;
    }
    return ((th<<16) | tl) / 2500;
  }

  // Format to string
  static char * hss(char * s) {
    ultoa(hs(),s,10);
    int n = strlen(s);
    s[n+1] = '\0';
    s[n]   = s[n-1];
    s[n-1] = s[n-2];
    s[n-2] = '.';
    return s;
  }
};
 
void setup() {                  
  // Timer
  timer::init();
  
  Serial.begin(9600); // For debugging
 
  // Init SD card 
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    while (true);
  }
  Serial.println("card initialized.");  
  
  // Open new file
  int i = 0;
  do {
    sprintf(filename, "s%04d.csv", i);
    i++;
  } while (SD.exists(filename));  
  Serial.print("Using file: ");
  Serial.println(filename);

  timer::reset();
}

void loop() {
  // Update index
  myIndex++;

  // Measure
  uint32_t sumv = 0; // Sum 
  uint32_t sumw = 0; // Sum weighted
  for (int i=0; i<SAMPLES; i++) {
    uint16_t v = analogRead(mic); // Should read about 1.65V or 340(ish) when silent
    sumv += v;
    sumw += (v-silent)*(v-silent);
  }

  // Calculate
  silent = (2 * sumv / SAMPLES + 1) / 2;
  float runavg = sqrt(sumw/SAMPLES);

  // Format  
  String dataString = "";
  char datastr[100];
  char tmpstr[24];
  timer::hss(datastr); // Begin with current time
  strcat(datastr,",");
  dtostrf(runavg, 1, 2, datastr+strlen(datastr));
  strcat(datastr,",");
  itoa(silent, datastr+strlen(datastr), 10);

  // Log
  File dataFile = SD.open(filename, FILE_WRITE);
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(datastr);
    dataFile.flush();
    dataFile.close();
    Serial.println(datastr);
  }
  else {
    Serial.println("error opening file");
  } 
}

