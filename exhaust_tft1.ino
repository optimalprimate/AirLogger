#include <TFT.h> // Hardware-specific library
#include <SPI.h>

#define CS   10
#define DC   9
#define RESET  8  

TFT myScreen = TFT(CS, DC, RESET);

int CO_val = 0; //define var to hold reading
int SND_val = 0; //define var to hold reading
int sensorvaluestart = 0;
int sensorvalueend = 0;
// int timedif = 0;
char COPrintout[4];
char SNDPrintout[4];

void setup() {
  
  myScreen.begin();  
  myScreen.background(0,0,0);  // clear the screen with black
  myScreen.stroke(255,255,255);
  // static text
  myScreen.text("Initialised",0,0);
  
  // initialize the serial communication:
  Serial.begin(9600);
   }

void loop() {
myScreen.background(0,0,0);  // clear the screen with black

CO_val = analogRead(A0);   // read CO sensor
Serial.println("CO = ");
Serial.println(CO_val);
SND_val = analogRead(A2);   // read sound sensor
Serial.println("SND = ");
Serial.println(SND_val);

myScreen.text("CO Value = ",0,10);

String CO_val_str(CO_val);
CO_val_str.toCharArray(COPrintout, 4);
myScreen.text(COPrintout,0,25);

String SND_val_str(SND_val);
SND_val_str.toCharArray(SNDPrintout, 4);
myScreen.text("Sound Value = ",0,40);
myScreen.text(SNDPrintout,0,50);

delay(5000);
} //end of loop
