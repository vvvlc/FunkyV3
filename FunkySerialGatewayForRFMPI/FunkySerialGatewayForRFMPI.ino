/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(38400);  
  while (!Serial) {
    LEDPulse(20);
    ; // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(13, OUTPUT);

  Serial1.begin(38400);    
}

/*      Breathing animation on L LED indicates bootloader is running */
uint16_t LLEDPulse;
void LEDPulse(int intensity)
{
        LLEDPulse++;
        uint8_t p = LLEDPulse >> 8;
        if (p > 127)
                p = 254-p;
        p += p;
        if (((uint8_t)LLEDPulse) > p)
                //L_LED_OFF();
                analogWrite(13,0);
        else
                //L_LED_ON();
                analogWrite(13,80);
}

void loop() {
  // By default, the last intialized port is listening.
  // when you want to listen on a port, explicitly select it:
  LEDPulse(80);

//  Serial.println("Data from port one:");
  // while there is data coming in, read it
  // and send to the hardware serial port:
  while (Serial1.available() > 0) {
    LEDPulse(255);
    char inByte = Serial1.read();
    Serial.write(inByte);
    LEDPulse(0);
  }
  if (Serial.available()) {
        LEDPulse(255);
    while (Serial.available() > 0) {
      char inByte = Serial.read();    
      Serial1.write(inByte);
    }
    LEDPulse(0);
  }    
  
}

