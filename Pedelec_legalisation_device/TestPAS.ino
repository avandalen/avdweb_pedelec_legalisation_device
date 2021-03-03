#if !ATtiny85
#include <assert.h>

Pas pasTest(testPinIn, 1000, 10);

void testPASforward()
{ pinMode(testPinOut, OUTPUT);  
  Timer1.initialize();
  Timer1.pwm(testPinOut, 600, 1023000);     
  while(1)
  { if(pasTest.poll())
    { assert(pasTest.pulseWidth >= 599);
      assert(pasTest.pulseWidth <= 601);
      assert(pasTest.pedalForward == 1);
      Serial << F("\ntestPASforward\n");
      Serial << pasTest.pedalForward, pasTest.period, pasTest.pulseWidth, pasTest.pulseWidthLow;
      break;
    }
  }
}

void testPASbackward()
{ pinMode(testPinOut, OUTPUT);  
  Timer1.initialize();
  Timer1.pwm(testPinOut, 490, 1023000);  
  while(1)
  { if(pasTest.poll())
    { assert(pasTest.pulseWidth >= 489);
      assert(pasTest.pulseWidth <= 491);
      assert(pasTest.pedalForward == 0);
      Serial << F("\ntestPASbackward OK\n");
      Serial << pasTest.pedalForward, pasTest.period, pasTest.pulseWidth, pasTest.pulseWidthLow;
      break;
    }
  }
}

void testPASnoPedaling()
{ pinMode(testPinOut, INPUT);
  delay(1000);
  while(1)
  { pasTest.poll();
    { assert(pasTest.pedalForward == 0);
      Serial << F("\ntestPASnoPedal OK\n");
      Serial << pasTest.pedalForward, pasTest.period, pasTest.pulseWidth, pasTest.pulseWidthLow;
      break;
    }
  }
}

void testPASonBike()
{ while(1)
  { pas.poll();    
    if(!pas.pedalForward) digitalWrite(ledPin, HIGH);
    else digitalWrite(ledPin, LOW);
  }
}
#endif


