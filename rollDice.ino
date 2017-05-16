/* See NOTICE file for copyright and licensing information */

static const byte digitMap[] = {
  B00111111, // 0   "0"          AAA           //a =7, b = 6, c = 4, d = 2, e = 1, f = 9, g = 10, dp =5
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
                            //a, b, c, d, e, f, g,  dp
const int alphaToIndex[] =  {3,  2, 8, 7, 6, 4, 5,  9};//{ 7,6,4,2,1,9,10,5};

int turnLow = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  for(int i = 2; i <= 10; ++i) {
    pinMode(i, OUTPUT);
  }
  randomSeed(analogRead(0));
  int ran = random(1,7);
  for(int i = 0; i < ran + 12; i++){
    int k = i % 6 + 1;
    displayDigit(k, LOW);
    delay(15*i + 100);
  }
  displayDigit(ran, HIGH);
}

//lower case only
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

void displayDigit(int index, int period) {
   byte d = digitMap[index];
   for(int i = 0; i < 7; i++) {
    int j = i;
      if(( (d >> j) & 0x1) > 0) { //then display this one
        pinMode(alphaToIndex[i], HIGH);
      } else {
        pinMode(alphaToIndex[i], LOW);
      }
   }
   pinMode(alphaToIndex[7], period);
}

void turnLowPause() {
  for(int i = 2; i <= 10; i++) {
    pinMode(i, LOW);
  }
  delay(200);
}

// the loop function runs over and over again forever
void loop() {

}
