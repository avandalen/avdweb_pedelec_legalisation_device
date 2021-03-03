/* Pedelec_legalisation_device

Take Attiny85 (internal 1MHz clock)

Release Notes
*/

#define ATtiny85 1

#include <Arduino.h>
#include "PLD.h"

#if !ATtiny85
//#include <TimerOne.h> // comment out for ATtiny85 with // (Arduino bug)//doen
//#include "Albert.h" // comment out for ATtiny85 with // (Arduino bug)//doen
#include <FreqPeriodCounter.h>
#include <Streaming.h>
#include "Tests.h"
#endif

// DEFINITIONS
#define maxPedalPeriodSec 3
#define pasForwardHighLong 1 // if PAS sensor is reversed take 0
#define numberPASmagnets 5
#define wheelCircumferenceMetre 2.185 // Koga: 2.16
#define numberOfMagnetsPerWheel 1 // better take 2
#define max_kmh 31 // 25kmh * 1.25 (27.5)
#define debounceTime_msec 10
#define msPerSec 998 // calibrate ATtiny85 

// PINS
#if ATtiny85
const byte pasPin = 4; // pin3
const byte wheelSpeedPin = 1; // pin6
const byte brakePin = 3; // pin2
const byte ledPin = 0; // pin5
//const byte ledPin = 4; // test on ISP programmer
const byte buzzerPin = 0;
#else
const byte pasPin = 2;
const byte wheelSpeedPin = 6;
const byte brakePin = 6;
const byte ledPin = 13;
const byte buzzerPin = 5;
const byte testPinIn = 3; // connect to testPinOut
const byte testPinOut = 9;
#endif

// Compile time calculations
const long pasTimeOut_msec = (float) msPerSec * maxPedalPeriodSec / numberPASmagnets; // 1400 
const long maxKmh_msec = (float) msPerSec * wheelCircumferenceMetre * 0.06 * 60 / (max_kmh * numberOfMagnetsPerWheel); // 282
const int kmhXwheelPeriod_msec = (float) msPerSec * wheelCircumferenceMetre * 0.06 * 60 / numberOfMagnetsPerWheel; // 7775

Pas pas(pasPin, pasTimeOut_msec, debounceTime_msec);
FreqPeriodCounter wheel(wheelSpeedPin, millis, debounceTime_msec);

void setup(void) 
{ pinMode(buzzerPin, OUTPUT);
  blinkLed1(ledPin);
  //calibrateTimer();
  //testAll();
}

void loop(void) 
{ if(limpMode()) 
  { brake(0);
    return;
  }
  pas.poll();
  wheel.poll(); 
  if(!pas.pedalForward | (wheel.period < maxKmh_msec)) brake(1);
  else brake(0);
  //digitalWrite(buzzerPin, !digitalRead(buzzerPin)); // sound test
}

/*
  if(!pas.pedalForward | wheel.period==0 | (wheel.elapsedTime > minKmh_msec) |
     (wheel.period < maxKmh_msec) | (wheel.period > minKmh_msec)
*/


