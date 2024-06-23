#include <Arduino.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

#include <SD.h>

#include <SPI.h> 
#include <movingAvg.h>
//#include "FS.h"
//#include "SD.h"
#include "SPI.h"
#include <EEPROM.h>
#include "Nextion.h"



// Custom Files
#include "pitches.h"
#include "variables.h"
#include "helperFunctions.h"
#include "theAlgorithm.h"




void setup() {
  
  delay(10);              // Allow Everything to Powerup Correctly

  Serial.begin(115200);   // For Computer Communication (Debugging Line)
  Serial2.begin(9600);    // For Display Communcations
  
  nexInit();              // Initialize Display - Starts on Logo Screen
  sdFileTitleANDSET();          // Update test # in memory && Update filename  
  hallInit();             // Setup GPIO Interup For Hall Effect Sensor
  ledInit();              // Setup LED & Flash Once 

  displayLoadPage();      // Change Display to Loading Page
  progUpdate(sProg, 10);  // Progress Bar (Visual)

//  sdCardInit();           // Initialize SD Card (checks !SDOFF inside)

  progUpdate(sProg, 80);

  // Open Dev File && Print Header
//  if(!SDOFF) {
//    myFile = SD.open(fileName, FILE_WRITE);
//    myFile.print("Time,Angle Y,MPH");
//  }

  accInit();              // Initialize MPU6050 
  
  angleAvg.begin();       // Start Angle Average
  mphAvg.begin();         // Start MPH Average 

  progUpdate(sProg, 100);

  displayHomePage();
//  if(!SDOFF) tFile.setText(filen);

  bCAL.attachPop(bCALCallback, &bCAL);
  bSET.attachPop(bSETCallback, &bSET);
  bSIZE.attachPop(bSIZECallback, &bSIZE);
  bDIF.attachPop(bDIFCallback, &bDIF);
  bSAVE.attachPop(bSAVECallback, &bSAVE);
  bGEAR.attachPop(bGEARCallback, &bGEAR);
  
  digitalWrite(LEDPIN, HIGH);

}


void loop() {
    
  if(setPres){
    settings_loop();            // ONLY FOR SETTINGS
    delay(1);
  }
  else{
    mpu6050.update();           // Allow MPU to update its values
    
//    if(!SDOFF) myFile.flush();
    
    if (mRUN_TIME - timer > sDELAY) {
      
      curAngle  = (-1.0) * ((double)mpu6050.getAngleY() - (double)calibrationA);     // Get New Angle
      avgAngle  = angleAvg.reading(curAngle);       // Negative angle for sensor orientaion (Into Average)
//      Serial.println( (double)calibrationA );
       
  
//      if(!SDOFF) myFileUpdate();  // Add Entry to myFile (SD Card)
      
      valuesUpdate();             // Update Display Values
      timer = mRUN_TIME;          // Reset Timer
      
      algo();
      
      
    }


    
    avgMPH      = mphAvg.reading(MPH);    // MPH Into Average
    
    if(hall.pressed){
      timerNew  = mRUN_TIME;
      hall.pressed = false;
    }
    
    calcMPH();
    nexLoop(home_nex_list);   // Check Display for button presses  
  }
  
}
