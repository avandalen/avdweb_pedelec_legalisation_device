/* 
Forward pedaling:
    _______     _____
   |       |   |
___|   .   |___|

When pedaling forward pulseWidth > pulseWidthLow
*/

Pas::Pas(byte pin, unsigned long timeOut, unsigned debounceTime):
timeOut(timeOut), pedalForward(0), FreqPeriodCounter(pin, millis, debounceTime)
{ 
}

bool Pas::poll()
{ if(FreqPeriodCounter::poll()) // if a complete period is measured
  { if((pasForwardHighLong & (pulseWidth > pulseWidthLow)) | (!pasForwardHighLong & (pulseWidth < pulseWidthLow))) pedalForward = true;
    else pedalForward = false;
  }
  if((period > timeOut)|(elapsedTime > timeOut)) pedalForward = false; 
}

void openDrain1(byte pin, bool value)
{ if(value) pinMode(pin, INPUT);
  else pinMode(pin, OUTPUT); 
  digitalWrite(pin, LOW);  
}

void blinkLed1(byte pin, int n)
{ pinMode(ledPin, OUTPUT);
  for(byte i=0; i<n; i++)
  { digitalWrite(pin, HIGH);       
    delay(100);                 
    digitalWrite(pin, LOW);   
    delay(100);
  }
}

void brake(bool brake)
{ openDrain1(brakePin, !brake);
  digitalWrite(ledPin, brake);
}

// Adjust msPerSec to get every second a tick
void calibrateTimer() 
{ static long lastTime;
  static bool b;
  while(1)
  { long time = millis();
    if((time - lastTime) >= msPerSec)
    { lastTime = time;
      b = !b;
      digitalWrite(buzzerPin, b);
    }
  }
}

bool limpMode()
{ static bool _limpMode=0, startUp=1;
  pinMode(brakePin, INPUT);
  if(startUp)
  { startUp=0;
    if(digitalRead(brakePin) == 0) _limpMode = 1;
  }
  return _limpMode;
}


