#include <Adafruit_GFX.h>
#include <RGBmatrixPanel.h>

#define CLK 8
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);
uint16_t black = matrix.Color333(0, 0, 0);
long del = 18000000L;

uint16_t colors[] = {
  matrix.Color333(7, 0, 0),
  matrix.Color333(0, 7, 0),
  matrix.Color333(0, 0, 7),
  matrix.Color333(7, 7, 0),
  matrix.Color333(0, 7, 7),
  matrix.Color333(7, 0, 7),
  matrix.Color333(7, 7, 7)
};

void draw(uint16_t color);

void setup() {
  matrix.begin();
  matrix.fillScreen(black);
  randomSeed(analogRead(4));
}

void loop() {
  if(random(0, 5) != 0) {
    draw(colors[random(0, 7)]);
  } else {
    matrix.fillScreen(black);
    matrix.setCursor(0, 0);   // start at top left, with one pixel of spacing
    matrix.setTextSize(1);    // size 1 == 8 pixels high
   
    // print each letter with a rainbow color
    matrix.setTextColor(matrix.Color333(7,0,0));
    matrix.print('O');
    matrix.setCursor(5, 0);
    matrix.setTextColor(matrix.Color333(7,4,0)); 
    matrix.print('l');
    matrix.setCursor(10, 0);
    matrix.setTextColor(matrix.Color333(7,7,0));
    matrix.print('i');
    matrix.setCursor(15, 0);
    matrix.setTextColor(matrix.Color333(4,7,0)); 
    matrix.print('v');
    matrix.setCursor(21, 0);
    matrix.setTextColor(matrix.Color333(0,7,0));  
    matrix.print('e');
    matrix.setCursor(27, 0);
    matrix.setTextColor(matrix.Color333(0,7,0));  
    matrix.print('r');
    
    matrix.setCursor(14, 9);   // next line
    matrix.setTextColor(matrix.Color333(0,7,7)); 
    matrix.print('J');
    
    matrix.setCursor(1, 18);   // next line
    matrix.setTextColor(matrix.Color333(0,0,7)); 
    matrix.print('S');
    matrix.setTextColor(matrix.Color333(4,0,7)); 
    matrix.print('p');
    matrix.setTextColor(matrix.Color333(7,0,4));
    matrix.print('r');
    matrix.setTextColor(matrix.Color333(4,7,7)); 
    matrix.print("y");
    matrix.setTextColor(matrix.Color333(7,7,7)); 
    matrix.print("n"); 
  }
  
  delay(del);
}

void draw(uint16_t color) {
  matrix.fillScreen(black);
  
//Draw circles
  matrix.drawCircle(16, 16, 15, color);
  matrix.drawCircle(16, 12, 7, color);
  matrix.drawCircle(16, 20, 7, color);
  
//Now make them semi-circles
  for(int i = 12; i <= 20; ++i) {
    matrix.drawLine(9, i, 24, i, black);
  }
  
//Draw the lines
  matrix.drawLine(9, 10, 20, 25, color);
  matrix.drawLine(12, 8, 23, 22, color);
}
