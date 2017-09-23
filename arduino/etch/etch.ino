/*
 * Copyright 2017 Makerspace55
 * www.makerspace56.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */
#include <PinChangeInterrupt.h>
#include <PinChangeInterruptBoards.h>
#include <PinChangeInterruptPins.h>
#include <PinChangeInterruptSettings.h>

#define DEBUG 0

#define pinWheel1 9 // interrupt pin
#define pinDir1 5
#define pinWheel2 10 // interrupt pin
#define pinDir2 6

byte countWheel1 = 0;
byte countWheel2 = 0;
boolean event = false;

void setup() {
  // set pin to input with a pullup, led to output
  pinMode(pinWheel1, INPUT_PULLUP);
  pinMode(pinDir1, INPUT_PULLUP);
  attachPCINT(digitalPinToPCINT(pinWheel1), intWheel1, RISING);

  pinMode(pinWheel2, INPUT_PULLUP);
  pinMode(pinDir2, INPUT_PULLUP);
  attachPCINT(digitalPinToPCINT(pinWheel2), intWheel2, RISING);

  // Serial communication
  Serial.begin(11520);
}

void intWheel1(void) {
  // Switch Led state
  if (digitalRead(pinDir1)){
    countWheel1 += 1;
  }else{
    countWheel1 -= 1;
  }
  event = true;
}

void intWheel2(void) {
  // Switch Led state
  if (digitalRead(pinDir2)){
    countWheel2 += 1;
  }else{
    countWheel2 -= 1;
  }
  event = true;
}


void loop() {
#if DEBUG
    Serial.print(digitalRead(pinDir1), DEC);
    Serial.print(digitalRead(pinWheel1), DEC);
    Serial.print(digitalRead(pinDir2), DEC);
    Serial.println(digitalRead(pinWheel2), DEC);  
#endif
  if (DEBUG || event){
    event = false;
    int valueWheel1 = countWheel1;
    int valueWheel2 = countWheel2;
    countWheel1 = countWheel2 = 0;

    Serial.print(char(valueWheel1));
    Serial.println(char(valueWheel2));
  }
  delay(200);
}
