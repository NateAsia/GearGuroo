/*****************************************
 *      Helper Functions - GearGuroo
 ******************************************/

void ARDUINO_ISR_ATTR isr(void* arg) {
    Sensor* s = static_cast<Sensor*>(arg);
    s->numberOfDetections += 1;
    s->pressed = true;
}

void calcMPH() {
  
  t = timerNew-timerLast;
  
  if((mRUN_TIME) - timerNew  > 4500){
    MPH=0;
  }
  
  if(t < sDELAY) return;  // Don't Change MPH
  
  timerLast=timerNew;

  RPM         = ((double)60 * 1000) / (t);

  if ( ((RPM * Diameter * 3.1415 * 60) / 63360 > 40 ) ){} // Dont change mph
  else{
    MPH  = (double)(RPM * Diameter * 3.1415 * 60) / (double)63360 ;
  }
}


// I/O Initializations
void hallInit(){
  pinMode(hall.PIN,  INPUT);
  attachInterruptArg(hall.PIN, isr, &hall, FALLING);
}

void ledInit(){
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);
  delay(10);
  digitalWrite(LEDPIN, HIGH);
  delay(100);
  digitalWrite(LEDPIN, LOW);
}

void accInit(){
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}

// Touch Button CallBacks
void bCALCallback(void *ptr){
  calPres = true;
  Serial.println("CAL");
}

void bSETCallback(void *ptr){
  setPres = true;
  Serial.println("SET\n");
}

void bSIZECallback(void *ptr){
  sizePres = true;
  Serial.println("SIZE\n");
}

void bDIFCallback(void *ptr){
  difPres = true;
  Serial.println("DIF\n");
}

void bSAVECallback(void *ptr){
  savePres = true;
  Serial.println("SAVE\n");
}

void bGEARCallback(void *ptr){
  gearPres = true;
  Serial.println("GEAR\n");
}


// SD Card Functions
void sdFileTitleANDSET() {
    EEPROM.begin(EEPROM_SIZE);
    fileNumber = EEPROM.read(0);
    fileNumber +=1;
    EEPROM.write(0, fileNumber);
    EEPROM.commit();

    userDiff = EEPROM.read(1);
    if(userDiff==0 || userDiff > 3){
      userDiff=1;
    }
    Diameter = EEPROM.read(2);
    if(Diameter==0 || Diameter > 30){
      Diameter=27;
    }
    numGears = EEPROM.read(3);
    if(numGears==0 || numGears > 30){
      numGears=9;
    }
    calibrationA = EEPROM.readFloat(4);
    
    
    sprintf (fileName, "/test%03d.txt", fileNumber);
    sprintf (filen, "test%03d.txt", fileNumber);
    Serial.println(filen);
}

//void sdCardInit(){
//  while ( !SDOFF && !SD.begin(SD_CS_PIN)) {
//    Serial.println(".");
//    digitalWrite(LEDPIN, LOW);
//    delay(10);
//    digitalWrite(LEDPIN, HIGH);
//    delay(10);
//    digitalWrite(LEDPIN, LOW);
//    delay(200);
//  }
//}

//void myFileUpdate(){
//      myFile.println();
//      myFile.print(mRUN_TIME);  // TIME (ms)
//      myFile.print(",");
//      myFile.print(curAngle);                   // ANGLE Y
//      myFile.print(",");
//      myFile.print(MPH);                        // MPH
//}

// Gear Action Functions 
  
  // Buzzer Functions
void buzzHigh(){
    int noteDuration = 1000 / noteDurations[0];
    tone(BUZZZER_PIN, melody[0], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(BUZZZER_PIN);
    prevGear=recGear;
}

void buzzLow(){
    int noteDuration = 1000 / noteDurations[1];
    tone(BUZZZER_PIN, melody[1], noteDuration);
  
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(BUZZZER_PIN);
    prevGear=recGear;
}

void gearChangeCheck(){ 
    if      (recGear < prevGear){
      buzzLow();
      tFile.Set_background_crop_picc(3);
      changedPic = true;
    }
    else if (recGear>prevGear){
      // Change Background
      buzzHigh();
      tFile.Set_background_crop_picc(2);      
      changedPic = true;
    }
    else{
      if(changedPic){
        tFile.Set_background_crop_picc(1);      
        changedPic = false;
      }
    }
}


// Display Functions 

void progUpdate(NexSlider p, int percent){
  
    p.getValue(&counter); 
    
    if(counter<percent){                // Go Up
      while(counter<percent){
          sProg.setValue(counter);
          counter ++; 
    
      }
    }
    
    else{                         // Go Down
      while(counter>percent){
        sProg.setValue(counter);
        counter --; 
    
      }
    }
    
  counter =0;
}

void displayLoadPage(){
  Serial2.print("page 2");
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);
}

void displayHomePage(){
  Serial2.print("page 0");
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);
}

void displaySettingsPage(){
  Serial2.print("page 3");
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);
}

void valuesUpdate(){
  
    nMPH.setValue(avgMPH);
    nGear.setValue(recGear);
    sprintf(text, "%d", avgAngle);
    nAngle.setText(text);
    
}

//void wsUpdate(){
//      WebSerial.println();
//      WebSerial.print((uint32_t)mRUN_TIME);  // TIME (ms)
//      WebSerial.print(",");
//      WebSerial.print((double)curAngle);                   // ANGLE Y
//      WebSerial.print(",");
//      WebSerial.print((double)MPH);                        // MPH
//  
//}

void settings_loop(){

      if(prevGear != -1){

        displaySettingsPage();

        sprintf(text, "%d", Diameter);
        bSIZE.setText(text);

        sprintf(text, "%f", calibrationA);
        bCAL.setText(text);

        sprintf(text, "%d", numGears);
        bGEAR.setText(text);

        if(userDiff == 1) sprintf(text, "BEGINNER");
        if(userDiff == 2) sprintf(text, "MODERATE");
        if(userDiff == 3) sprintf(text, "INTENSE");
        bDIF.setText(text);

        prevGear = -1;
      }
  
      if(savePres){

        EEPROM.write(1, userDiff);
        EEPROM.write(2, Diameter);
        EEPROM.write(3, numGears);
        EEPROM.writeFloat(4, calibrationA);
        EEPROM.commit();
        
        ESP.restart();
      }

      

      if(sizePres){
        if(Diameter==30)  Diameter = 10;
        else              Diameter +=1;

         // UPDATE SCREEN
        sprintf(text, "%d", Diameter);
        bSIZE.setText(text);


        
        
        sizePres=false;
      }

      if(calPres){
        mpu6050.update();
        calibrationA=(double)mpu6050.getAngleY();
        
        sprintf(text, "%f", calibrationA);
        bCAL.setText(text);
        
        calPres=false;
      }
      
      if(difPres){
        if(userDiff == 3) userDiff = 1;
        else              userDiff +=1;

        if(userDiff == 1) sprintf(text, "BEGINNER");
        if(userDiff == 2) sprintf(text, "MODERATE");
        if(userDiff == 3) sprintf(text, "INTENSE");
        
        bDIF.setText(text);

        difPres=false;
      }

      if(gearPres){
        if(numGears == 30) numGears = 1;
        else               numGears +=1;

        sprintf(text, "%d", numGears);
        bGEAR.setText(text);

        gearPres=false;
      }

      

  
  nexLoop(settings_nex_list);
}
