#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>

float midi[127];
int A_four = 440;

float lightVal;

int modeControl = 0;
int buttonA = 4;
int buttonB = 5;
int buttonSwitch = 7;
volatile bool buttonAFlag = 0;
volatile bool buttonBFlag = 0;
volatile bool buttonSwitchFlag = 0;
volatile bool switchState = 0;

int score = 0;

const uint8_t spREADY[]         PROGMEM = {0x6A,0xB4,0xD9,0x25,0x4A,0xE5,0xDB,0xD9,0x8D,0xB1,0xB2,0x45,0x9A,0xF6,0xD8,0x9F,0xAE,0x26,0xD7,0x30,0xED,0x72,0xDA,0x9E,0xCD,0x9C,0x6D,0xC9,0x6D,0x76,0xED,0xFA,0xE1,0x93,0x8D,0xAD,0x51,0x1F,0xC7,0xD8,0x13,0x8B,0x5A,0x3F,0x99,0x4B,0x39,0x7A,0x13,0xE2,0xE8,0x3B,0xF5,0xCA,0x77,0x7E,0xC2,0xDB,0x2B,0x8A,0xC7,0xD6,0xFA,0x7F};
const uint8_t spTO[]                PROGMEM ={0x02,0xD8,0x51,0x3C,0x00,0xC7,0x7A,0x18,0x20,0x85,0xE2,0xE5,0x16,0x61,0x45,0x65,0xD9,0x6F,0xBC,0xE3,0x99,0xB4,0x34,0x51,0x6B,0x49,0xC9,0xDE,0xAB,0x56,0x3B,0x11,0xA9,0x2E,0xD9,0x73,0xEB,0x7A,0x69,0x2A,0xCD,0xB5,0x9B,0x1A,0x58,0x2A,0x73,0xF3,0xCD,0x6A,0x90,0x62,0x8A,0xD3,0xD3,0xAA,0x41,0xF1,0x4E,0x77,0x75,0xF2};
const uint8_t spPLAY[]              PROGMEM ={0x06,0xC8,0x55,0x54,0x01,0x49,0x69,0x94,0xC4,0xA4,0x1C,0xE3,0x8A,0xD3,0x93,0x19,0xAF,0x24,0xE4,0x68,0xE1,0x4D,0xBC,0x92,0x58,0x22,0x95,0x27,0xF1,0x4A,0x53,0xF5,0x10,0x99,0x26,0xB3,0x68,0x75,0x29,0x12,0xE2,0x53,0xBB,0x74,0x31,0x52,0x64,0x4F,0xD8,0xDA,0xA7,0x3E,0x3A,0xF6,0xAC,0x2C,0x13,0xFA,0xA0,0x39,0xBA,0x33,0x88,0xEB,0x8D,0x92,0xB9,0x70,0xA1,0x0F,0x00,0x00};
const uint8_t spCORRECT[]           PROGMEM ={0x0E,0x70,0xC7,0x49,0x00,0x3E,0x86,0xA5,0x58,0x8D,0x2C,0x53,0xCD,0x76,0x8B,0x56,0x98,0x23,0x95,0xA2,0x99,0x6B,0x95,0x9B,0xDA,0xAC,0xCA,0x27,0x6D,0xF1,0x8D,0xBD,0xAB,0x59,0xF7,0x26,0xB5,0xBE,0x73,0x79,0x4D,0x90,0xDC,0xB9,0x21,0x0C,0x28,0x8F,0x91,0x29,0x47,0x00,0x00,0x01,0x0C,0xED,0xAA,0x80,0xE5,0xA2,0x05,0xD0,0x74,0x3B,0x02,0xBC,0x4B,0x7A,0x00,0x00};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  CircuitPlayground.begin();

  generateMIDI();

  pinMode(buttonA, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(buttonA), buttonAPress, FALLING);

  pinMode(buttonB, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(buttonB), buttonBPress, FALLING);

  pinMode(buttonSwitch, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonSwitch), buttonSwitchFlip, CHANGE);
  
  CircuitPlayground.speaker.say(spREADY);
  CircuitPlayground.speaker.say(spTO);
  CircuitPlayground.speaker.say(spPLAY);
}

void loop() {
  if(buttonAFlag) {
    delay(5);
    modeControl --;
    buttonAFlag = 0;
  }
  if(buttonBFlag) {
    delay(5);
    modeControl ++;
    buttonBFlag = 0;
  }
  if(buttonSwitchFlag) {
    delay(5);
    switchState = digitalRead(buttonSwitch);
    buttonSwitchFlag = 0;
  }
if(switchState) {
    switch (modeControl) {
    case 0:
    blank();
    break;
    case 1:
    songHalo();
    break;
    case 2:
    songCODZombies();
    break;
    case 3:
    songDonkeyKong();
    break;
    case 4:
    blank();
    break;
    default:
    break;
   }
   if(buttonAFlag && buttonBFlag) {
    score += 3;
    buttonAFlag = 0;
    buttonBFlag = 0;
    Serial.println(score);
    CircuitPlayground.setPixelColor(score - 2, 0, 255, 255);
    CircuitPlayground.speaker.say(spCORRECT);
    }
  }


    else {
    switch (modeControl) {
    case 0:
    blank();
    break;
    case 1:
    songMario();
    break;
    case 2:
    songUndertale();
    break;
    case 3:
    songMinecraft();
    break;
    case 4:
    blank();
    break;
    default:
    break;
   }
   
   
   if(buttonAFlag && buttonBFlag) {
    score++;
    buttonAFlag = 0;
    buttonBFlag = 0;
    Serial.println(score);
    CircuitPlayground.setPixelColor(score - 1, 0, 255, 0);
    CircuitPlayground.speaker.say(spCORRECT);
    }
  }
}
  




  



void songMario() {
int song1[11][2] = {
  {76, 100},
  {76, 100},
  {127, 100},
  {76, 100},
  {127, 100},
  {72, 100},
  {76, 200},
  {79, 200},
  {127, 200},
  {67, 200},
  {127, 200},
};
for(int i = 0; i < sizeof(song1) / sizeof(song1[0]); i++) // Calculate how many rows are in the array using: sizeof(song) / sizeof(song[0])
  {
CircuitPlayground.playTone(midi[song1[i][0]], song1[i][1]);
}
CircuitPlayground.playTone(midi[127], 500);
}

void songHalo() {
  int song2[23][2] = {
  {56, 600},
  {63, 600},
  {58, 1200},
  {56, 600},
  {65, 450},
  {63, 150},
  {58, 1200},
  {65, 450},
  {67, 150},
  {68, 450},
  {63, 150},
  {70, 600},
  {68, 450},
  {67, 150},
  {65, 600},
  {63, 600},
  {65, 600},
  {55, 600},
  {56, 600},
  {65, 1200},
  {55, 600},
  {56, 600},
  {65, 1800},
  };

for(int j = 0; j < sizeof(song2) / sizeof(song2[0]); j++) // Calculate how many rows are in the array using: sizeof(song) / sizeof(song[0])
  {
CircuitPlayground.playTone(midi[song2[j][0]], song2[j][1]);
 }
 CircuitPlayground.playTone(midi[127], 500);
}

void songUndertale() {
int song3[56][2] = {
  {62, 50},
  {62, 50},
  {74, 100},
  {69, 100},
  {127, 50},
  {68, 50},
  {127, 50},
  {67, 50},
  {127, 50},
  {65, 50},
  {127, 50},
  {62, 50},
  {65, 50},
  {67, 50},
  {60, 50},
  {60, 50},
  {74, 100},
  {69, 100},
  {127, 50},
  {68, 50},
  {127, 50},
  {67, 50},
  {127, 50},
  {65, 50},
  {127, 50},
  {62, 50},
  {65, 50},
  {67, 50},
  {59, 50},
  {59, 50},
  {74, 100},
  {69, 100},
  {127, 50},
  {68, 50},
  {127, 50},
  {67, 50},
  {127, 50},
  {65, 50},
  {127, 50},
  {62, 50},
  {65, 50},
  {67, 50},
  {58, 50},
  {58, 50},
  {74, 100},
  {69, 100},
  {127, 50},
  {68, 50},
  {127, 50},
  {67, 50},
  {127, 50},
  {65, 50},
  {127, 50},
  {62, 50},
  {65, 50},
  {67, 50},
  };

  for(int k = 0; k < sizeof(song3) / sizeof(song3[0]); k++) // Calculate how many rows are in the array using: sizeof(song) / sizeof(song[0])
  {
CircuitPlayground.playTone(midi[song3[k][0]], song3[k][1]);
}
CircuitPlayground.playTone(midi[127], 500);
}

void songMinecraft() {
  int song4[16][2] = {
  {71, 400},
  {69, 200},
  {64, 400},
  {67, 600},
  {71, 400},
  {69, 200},
  {64, 400},
  {62, 600},
  {71, 400},
  {69, 200},
  {64, 400},
  {67, 600},
  {71, 400},
  {69, 200},
  {64, 400},
  {62, 600},
};
for(int l = 0; l < sizeof(song4) / sizeof(song4[0]); l++) // Calculate how many rows are in the array using: sizeof(song) / sizeof(song[0])
  {
CircuitPlayground.playTone(midi[song4[l][0]], song4[l][1]);
 }
 CircuitPlayground.playTone(midi[127], 500);
}

void songCODZombies() {
   int song5[63][2] = {
  {83, 100},
  {76, 50},
  {83, 50},
  {71, 50},
  {76, 50},
  {83, 50},
  {71, 50},
  {76, 50},
  {83, 50},
  {71, 50},
  {76, 50},
  {83, 50},
  {71, 50},
  {76, 50},
  {83, 50},
  {83, 50},
  {76, 50},
  {76, 50},
  {83, 50},
  {71, 50},
  {76, 50},
  {83, 50},
  {71, 50},
  {76, 50},
  {83, 50},
  {71, 50},
  {76, 50},
  {83, 50},
  {71, 50},
  {76, 50},
  {83, 50},
  {84, 50},
  {76, 50},
  {76, 50},
  {84, 50},
  {72, 50},
  {76, 50},
  {84, 50},
  {72, 50},
  {76, 50},
  {84, 50},
  {72, 50},
  {76, 50},
  {84, 50},
  {72, 50},
  {76, 50},
  {84, 50},
  {86, 50},
  {76, 50},
  {76, 50},
  {86, 50},
  {72, 50},
  {76, 50},
  {84, 50},
  {72, 50},
  {76, 50},
  {84, 50},
  {72, 50},
  {76, 50},
  {84, 50},
  {72, 50},
  {76, 50},
  {84, 50},
};
for(int m = 0; m < sizeof(song5) / sizeof(song5[0]); m++) // Calculate how many rows are in the array using: sizeof(song) / sizeof(song[0])
  {
CircuitPlayground.playTone(midi[song5[m][0]], song5[m][1]);
 }
 CircuitPlayground.playTone(midi[127], 500);

}

void songDonkeyKong() {
  int song6[28][2] = {
  {60, 80},
  {60, 80},
  {69, 400},
  {65, 80},
  {67, 80},
  {65, 80},
  {62, 480},
  {62, 80},
  {62, 80},
  {70, 400},
  {69, 80},
  {70, 80},
  {69, 80},
  {64, 480},
  {64, 80},
  {64, 80},
  {72, 400},
  {69, 80},
  {70, 80},
  {72, 80},
  {74, 480},
  {65, 80},
  {67, 80},
  {69, 400},
  {62, 80},
  {64, 80},
  {65, 80},
  {62, 240},
};
for(int n = 0; n < sizeof(song6) / sizeof(song6[0]); n++) // Calculate how many rows are in the array using: sizeof(song) / sizeof(song[0])
  {
CircuitPlayground.playTone(midi[song6[n][0]], song6[n][1]);
 }
 CircuitPlayground.playTone(midi[127], 500);
}

void generateMIDI()
{
  for (int x = 0; x < 127; ++x)
  {
    midi[x] = (A_four / 32.0) * pow(2.0, ((x - 9.0) / 12.0));
    Serial.println(midi[x]);
  }
}

void buttonAPress() {
   buttonAFlag = 1;
}
void buttonBPress() {
  buttonBFlag = 1;
}
void buttonSwitchFlip() {
  buttonSwitchFlag = 1;
}

void blank() {

}
