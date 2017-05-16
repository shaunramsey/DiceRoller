/* See NOTICE file for copyright and licensing information */
/* Apache License 2.0 - See Notice*/
/* Copyright 2017, Shaun Ramsey, Chris Saul - See Notice */

/* v0.3 - added a function that tests each segment in order A-G,dp */
/* v0.2 - added comments and rearranged some code */


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

//map your a-g,dp to pins on the arduino...probably could do this in
//a more orderly fashion but this array allows us to mix things up
                            //a, b, c, d, e, f, g, dp
const int alphaToIndex[] =  {3,  2, 8, 7, 6, 4, 5, 9};//{ 7,6,4,2,1,9,10,5};




//mixed case and some are missing
void displayCharacter(char c) {
   c = tolower(c);
   int index = c - 'a';
   byte d = charMap[index];
   for(int i = 0; i < 8; i++) {
    int j = i;
      if(( (d >> j) & 0x1) > 0) { //then display this one
        pinMode(alphaToIndex[i], HIGH);
      } else {
        pinMode(alphaToIndex[i], LOW);
      }
   }
}


//display this particular digit
void displayDigit(int index, int period) {
   byte d = digitMap[index];
   for(int i = 0; i < 7; i++) {
    int j = i;
      if(( (d >> j) & 0x1) > 0) { //then display this one
        pinMode(alphaToIndex[i], HIGH); //turn this one on
      } else {
        pinMode(alphaToIndex[i], LOW); //turn this one off
      }
   }
   pinMode(alphaToIndex[7], period);
}


//not used but useful to turn all the segments off
void turnLowPause() {
  for(int i = 2; i <= 10; i++) {
    pinMode(i, LOW);
  }
  delay(200);
}


//test all the segments
void segmentTest() {
  for(int i = 0; i < 8; i++) {
    int previndex = i - 1;
    if(previndex < 0) previndex = 0;
    pinMode(previndex, LOW);
    pinMode(i, HIGH);
    delay(200);
  }
}


// first time - only when botting up does this run
void setup() {
  // init all these pins as output
  for(int i = 2; i <= 10; ++i) {
    pinMode(i, OUTPUT);
  }

   //do a segmentTest!
   segmentTest();
  randomSeed(analogRead(0)); //neat way to get a seed
  int ran = random(1,7);
  for(int i = 0; i < ran + 12; i++){
    int k = i % 6 + 1;
    displayDigit(k, LOW);
    delay(15*i + 100);
  }
  displayDigit(ran, HIGH);
}



// loop forever
void loop() {

}
