#if !ATtiny85

// Connect testPinIn to testPinOut for tests that use timer1

void testAll()
{ Serial.begin(9600); 
  Serial << "\n Test " << pasTimeOut_msec; // ,  = " "
 // testPASforward();
 // testPASbackward(); 
 // testPASnoPedaling();
    
  //testPASonBike(); 
  testWheelonBike();   
  //test_kmh();   
}

bool loopDuration_ms(bool _print, int intervalInNumberOfLoops)
{ static unsigned long lastLoopTime=0;
  static int i=0;
  unsigned long time = micros();
  int loopDuration = time - lastLoopTime;
  lastLoopTime = time;
  if(i++ > intervalInNumberOfLoops)
  { if(_print) Serial << " " << loopDuration;
    i=0;
    return true;
  }
  return false;
}

void test_kmh()
{ while(1)
  { wheel.poll();
//    Serial << endl << wheel.period, wheel.pulseWidthLow, (float)kmhXwheelPeriod_msec/wheel.period;
    Serial << endl << wheel.period;
  }
}

void testWheelonBike()
{ bool br=1;
  while(1)
  { wheel.poll();
    if(wheel.period==0 | (wheel.period < maxKmh_msec) | (wheel.period > minKmh_msec) | (wheel.elapsedTime > minKmh_msec)) br=1;
    else br=0;
    if(loopDuration_ms(0, 1000)) Serial << endl << br, wheel.period, wheel.elapsedTime;
  }
}

#endif



