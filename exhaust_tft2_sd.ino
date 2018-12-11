#include <TFT.h> // Hardware-specific library
#include <SPI.h>
#include <SD.h>

#define CS   10
#define SD_CS 4
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
unsigned long mstime;

void setup() {
  
  myScreen.begin();  
  myScreen.background(0,0,0);  // clear the screen with black
  myScreen.stroke(255,255,255);
  // static text
  
  // initialize the serial communication:
  Serial.begin(9600);

  // try to access the SD card
  myScreen.text("Initializing SD card...",0,0);
  Serial.print("Initializing SD card...");
  if (!SD.begin(SD_CS)) {
    myScreen.text("No SD Card Found",0,20);
    Serial.println("failed!");
    delay(3000);
    return;
  }
   myScreen.text("SD Card Found!",0,20);
  Serial.println("OK!");
   }

void loop() {

  // make a string for assembling the data to log:
  String dataString = "";

myScreen.background(0,0,0);  // clear the screen with black
myScreen.stroke(255,255,255);

CO_val = analogRead(A0);   // read CO sensor
Serial.println("CO = ");
Serial.println(CO_val);
SND_val = analogRead(A2);   // read sound sensor
Serial.println("SND = ");
Serial.println(SND_val);

//current on time in Seconds
mstime = millis();
mstime = mstime/1000;
//write values to string for logging
dataString += String(mstime);
dataString += ",";
dataString += String(CO_val);
//dataString += ",";


  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
File dataFile = SD.open("datalog.txt", FILE_WRITE);
  myScreen.stroke(255,50,100);
// if the file is available, write to it:
  if (dataFile) {
    myScreen.text("Writing to file...",0,80);
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    myScreen.text("Log Successful!",0,100);
  }
  // if the file isn't open, pop up an error:
  else {
    myScreen.text("error opening datalog.txt", 0,120);
  }

  

myScreen.text("CO Value = ",0,10);

String CO_val_str(CO_val);
CO_val_str.toCharArray(COPrintout, 4);
  myScreen.setTextSize(3);
myScreen.text(COPrintout,0,25);
  myScreen.setTextSize(1);

//String SND_val_str(SND_val);
//SND_val_str.toCharArray(SNDPrintout, 4);
//myScreen.text("Sound Value = ",0,40);
//myScreen.text(SNDPrintout,0,50);

delay(20000);
} //end of loop
