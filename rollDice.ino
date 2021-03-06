/* See NOTICE file for copyright and licensing information */
/* Apache License 2.0 - See Notice*/

/* Copyright 2017 Shaun Ramsey, Chris Saul

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.*/

/* v0.4 - changed pinMode to digitalWrite to be appropriate, used ! to show they're inverted, added variable roll timers, sped them up */
/* v0.3 - added a function that tests each segment in order A-G,dp */
/* v0.2 - added comments and rearranged some code */

const int clockPin = 11;
const int latchPin = 12;
const int dataPin = 13;

//a map of the digits
static const byte digitMap[] = {
  B00111111, // 0   "0"          AAA        
  B00000110, // 1   "1"         F   B	    
  B01011011, // 2   "2"         F   B
  B01001111, // 3   "3"          GGG
  B01100110, // 4   "4"         E   C
  B01101101, // 5   "5"         E   C
  B01111101, // 6   "6"          DDD
  B00000111, // 7   "7"
  B01111111, // 8   "8"
  B01101111, // 9   "9"
};

//a map of characters
static const byte charMap[] = {
 B01110111, //"a"
 B01111100, //"b"
 B00111001, // 67  'C'
 B01011110, // 68  'd'
 B01111001, // 69  'E'
 B01110001, // 70  'F'
 B00111101, // 71  'G'
 B01110110, // 72  'H'
 B00000110, // 73  'I'
 B00001110, // 74  'J'
 B01110110, // 75  'K'  Same as 'H'
 B00111000, // 76  'L'
 B00000000, // 77  'M'  NO DISPLAY
 B01010100, // 78  'n'
 B00111111, // 79  'O'
 B01110011, // 80  'P'
 B01100111, // 81  'q'
 B01010000, // 82  'r'
 B01101101, // 83  'S'
 B01111000, // 84  't'
 B00111110, // 85  'U'
 B00111110, // 86  'V'  Same as 'U'
 B00000000, // 87  'W'  NO DISPLAY
 B01110110, // 88  'X'  Same as 'H'
 B01101110, // 89  'y'
 B01011011, // 90  'Z'  Same as '2'
};

//This containts the segment order for GIS day 
const int segmentOrder[] = {3, 4, 0, 2, 1, 6, 5, 7};

//will adjust the digit bytes to match the arduino setup 
byte permute(byte d) {
  byte b = 0;
  for (int i=0; i<8; i++){
    //Does exactly what the Bitwrite line does but faster using bitshifts 
    b = b  | ( ( (d & ( 1 << i ) ) >> i ) << segmentOrder[i] );
    //bitWrite(b, segmentOrder[i], bitRead(d, i));
  }
  return b;
}

//mixed case and some are missing
void displayCharacter(char c) {
   c = tolower(c);
   int index = c - 'a';
   //uses XOR and the -1 value to invert the byte. 
   //XOR making the value true when they differ
   byte d = permute(charMap[index]) ^ -1;
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, d);
   digitalWrite(latchPin, HIGH);
}

void displayDigit(int index, int period) {
   //uses XOR and the -1 value to invert the byte. 
   //XOR making the value true when they differ
   byte d = permute(digitMap[index]) ^ -1;
   if (period == HIGH){
    d = d & 127; 
   }
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, d);
   digitalWrite(latchPin, HIGH);
}

//not used but useful to turn all the segments off
void turnOffPause(int pause_length) {
  byte d = B11111111;
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, d);
  digitalWrite(latchPin, HIGH);
  delay(pause_length);
}

//Segment tests the arduino where segments dont match the digit bytes 
void segmentTest() {
  for(int i = 0; i < 8; i++) {
    byte d = B11111111;
    bitWrite(d, segmentOrder[i], 0);
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, d);
    digitalWrite(latchPin, HIGH);
    delay(200);
  }
}

// first time - only when botting up does this run
void setup() {
  // init all these pins as output
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  //do a segmentTest!
  segmentTest();
  randomSeed(analogRead(0)); //neat way to get a seed

  int ran = random(1,7);  
  int dur = random(1,5);  //makes dice roll feel good

  for(int i = 0; i < ran + 6*dur; i++){
    int k = i % 6 + 1;
    displayDigit(k, LOW);
    delay(15*i + 20);
  }
  displayDigit(ran, HIGH);  //shows the rolled value
}

// loop forever
void loop() {
  //No loop for you
}
