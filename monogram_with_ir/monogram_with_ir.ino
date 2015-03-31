#include <Adafruit_GFX.h>
#include <RGBmatrixPanel.h>

#define CLK 8
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel* matrix;
long del = 18000000L;
int IRledPin =  13;

// LED bar toggle signal on and off durations in 10's of microseconds
int IRsignal[] = {
  890, 442,
  56, 54,
  58, 52,
  60, 52,
  56, 52,
  60, 52,
  58, 54,
  56, 52,
  58, 54,
  58, 164,
  58, 164,
  56, 164,
  60, 162,
  60, 164,
  56, 164,
  58, 164,
  58, 164,
  56, 54,
  58, 52,
  60, 162,
  58, 54,
  58, 162,
  58, 54,
  58, 52,
  58, 52,
  58, 166,
  56, 164,
  58, 54,
  56, 164,
  58, 54,
  56, 164,
  60, 162,
  58, 164,
  56, 3944,
  888, 220,
  58, 2942,
  890, 218,
  60, 2942,
  888, 220,
  58, 2942,
  890, 220,
  58, 2942,
  888, 220,
  60, 2940,
  890, 218,
  60, 2942,
  890, 218,
  60, 2940,
  890, 220,
  58, 0
};

void draw(uint16_t color);
void pulseIR(long microsecs);
void sendOnSignal();

void setup() {
//Turn on the LED bar
  pinMode(IRledPin, OUTPUT);
  sendOnSignal();
  delay(3000);
  
//Now power on the LED matrix
  matrix = new RGBmatrixPanel(A, B, C, D, CLK, LAT, OE, false);
  matrix->begin();
  matrix->fillScreen(matrix->Color333(0, 0, 0));
  randomSeed(analogRead(4));
}

void loop() {
  if(random(0, 5) != 0) {
    uint16_t colors[] = {
      matrix->Color333(7, 0, 0),
      matrix->Color333(0, 7, 0),
      matrix->Color333(0, 0, 7),
      matrix->Color333(7, 7, 0),
      matrix->Color333(0, 7, 7),
      matrix->Color333(7, 0, 7),
      matrix->Color333(7, 7, 7)
    };
    
    draw(colors[random(0, 7)]);
  } else {
    matrix->fillScreen(matrix->Color333(0, 0, 0));
    matrix->setCursor(0, 0);   // start at top left, with one pixel of spacing
    matrix->setTextSize(1);    // size 1 == 8 pixels high
   
    // print each letter with a rainbow color
    matrix->setTextColor(matrix->Color333(7,0,0));
    matrix->print('O');
    matrix->setCursor(5, 0);
    matrix->setTextColor(matrix->Color333(7,4,0)); 
    matrix->print('l');
    matrix->setCursor(10, 0);
    matrix->setTextColor(matrix->Color333(7,7,0));
    matrix->print('i');
    matrix->setCursor(15, 0);
    matrix->setTextColor(matrix->Color333(4,7,0)); 
    matrix->print('v');
    matrix->setCursor(21, 0);
    matrix->setTextColor(matrix->Color333(0,7,0));  
    matrix->print('e');
    matrix->setCursor(27, 0);
    matrix->setTextColor(matrix->Color333(0,7,0));  
    matrix->print('r');
    
    matrix->setCursor(14, 9);   // next line
    matrix->setTextColor(matrix->Color333(0,7,7)); 
    matrix->print('J');
    
    matrix->setCursor(1, 18);   // next line
    matrix->setTextColor(matrix->Color333(0,0,7)); 
    matrix->print('S');
    matrix->setTextColor(matrix->Color333(4,0,7)); 
    matrix->print('p');
    matrix->setTextColor(matrix->Color333(7,0,4));
    matrix->print('r');
    matrix->setTextColor(matrix->Color333(4,7,7)); 
    matrix->print("y");
    matrix->setTextColor(matrix->Color333(7,7,7)); 
    matrix->print("n"); 
  }
  
  delay(del);
}

void draw(uint16_t color) {
  matrix->fillScreen(matrix->Color333(0, 0, 0));
  
//Draw circles
  matrix->drawCircle(16, 16, 15, color);
  matrix->drawCircle(16, 12, 7, color);
  matrix->drawCircle(16, 20, 7, color);
  
//Now make them semi-circles
  for(int i = 12; i <= 20; ++i) {
    matrix->drawLine(9, i, 24, i, matrix->Color333(0, 0, 0));
  }
  
//Draw the lines
  matrix->drawLine(9, 10, 20, 25, color);
  matrix->drawLine(12, 8, 23, 22, color);
}

void pulseIR(long microsecs) {
  cli(); // Turns off any background interrupts
 
  while (microsecs > 0) {
   // 38 kHz is about 13 microseconds high and 13 microseconds low
   digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
   delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
   digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds
   delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
 
   // so 26 microseconds altogether
   microsecs -= 26;
  }
 
  sei(); // This turns them back on
}
 
void sendOnSignal() {
  for(int i = 0; i < 100; ++i) {
    pulseIR(IRsignal[i] * 10);
    ++i;
    delayMicroseconds(IRsignal[i] * 10);
  }
}
