/*****************************************
 *          THE ALGORITHM - GearGuroo
 ******************************************/

void algo() {
  curTime = mRUN_TIME;
  if (curTime - lastTime > 5000) {
    
    lastTime = curTime;
//    if (!numPts) {numPts =1;}
    // Average first numPts values in array
    angleAvg1 = 0;
    speedAvg1 = 0;
    
    for (int i = 0; i < numPts; i++) {
      angleAvg1 += data1[i][0];
      speedAvg1 += data1[i][1];
    }
    
    angleAvg1 /= numPts;
    speedAvg1 /= numPts;
    output = 0.04308572822360435 + -0.00541469*(float)angleAvg1 + 0.07278964*(float)speedAvg1;
    
    if (userDiff == 1) {
      output *= 0.9;
    }
    else if (userDiff == 3) {
      output *= 1.11;
    }
    
    newRec = round(output * numGears);

    Serial.print(newRec);
    Serial.print(" ");
    Serial.println(output);
    
    if ((newRec > recGear) && (recGear != numGears) ){recGear += 1;}
    else if( (newRec < recGear) && (recGear > 1)) {recGear -= 1;}
    numPts = 0;
    gearChangeCheck();          // Action to take
    
  }
  data1[numPts][0] = curAngle;
  data1[numPts][1] = MPH;
  numPts++;
}
