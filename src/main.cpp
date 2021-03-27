#include <Adafruit_NeoPixel.h>
#include <iostream>

#define MATRIX_X 32
#define MATRIX_Y 8
#define MATRIX_UNITS MATRIX_X * MATRIX_Y
#define FRAMES_NUM 2
#define MATRIX_PIN D4
#define FPS 60
#define FPS_PER_FRAME 20

const String mtxinput = 
"0000 0000 0000 0000 0000 0000 0000 0000 " 
"0000 0001 1000 1100 0110 0111 0000 0000 "
"0000 0101 0101 0010 1000 0100 0100 0000 "
"0011 1001 1001 0010 0110 0111 0011 1000 "
"0000 0101 0101 0010 0001 0100 0100 0000 "
"0010 0001 0100 1100 0110 0111 0001 0100 "
"0101 0000 0000 0000 0000 0000 0000 1000 "
"0000 0000 0000 0000 0000 0000 0000 0000 "

"0000 0000 0000 0000 0000 0000 0000 0000 "
"0000 0001 1000 1100 0110 0111 0000 0000 "
"0000 0101 0101 0010 1000 0100 0100 0000 "
"0011 1001 1001 0010 0110 0111 0011 1000 "
"0000 0101 0101 0010 0001 0100 0100 0000 "
"0101 0001 0100 1100 0110 0111 0000 1000 "
"0010 0000 0000 0000 0000 0000 0001 0100 "
"0000 0000 0000 0000 0000 0000 0000 0000";
 
uint8_t ledmatrix[FRAMES_NUM][MATRIX_UNITS];
Adafruit_NeoPixel matrix(MATRIX_UNITS, MATRIX_PIN, NEO_GRB + NEO_KHZ800);
int count = 0;

void setup() {

  Serial.begin(9600);
  
  delay(250);

  String mtxInputBuffer = mtxinput;
  
  mtxInputBuffer.replace(" ", "");

  int frameIndex = 0;
  int pixelIndex = 0;
  for (unsigned int i = 0; i < mtxInputBuffer.length(); i++) {

    char c = mtxInputBuffer.charAt(i);

    if (pixelIndex > MATRIX_UNITS - 1) {

      pixelIndex = 0;
      frameIndex++;

    }

    ledmatrix[frameIndex][pixelIndex] = c - '0';

    pixelIndex++;

  }

  matrix.begin();
  matrix.setBrightness(20);
  matrix.show();

}

int intdiv(int divident, int divisor) {

  return (int)(divident / divisor);

}

int matrixRotate(int x) {

  int line = intdiv(x, 32);
  int row = x % 32;
  int y = (8 * row) + line;
  if (row % 2) {
    return y + (7 - (line * 2));
  } else {
    return y;
  }

}

void lightUp(int frame) {

  matrix.clear();

  for (int i = 0; i < 256; i++) {

    uint32_t color = matrix.Color(255, 255, 255);
    matrix.setPixelColor(matrixRotate(i), color * ledmatrix[frame][i]);

  }

  matrix.show();

}

void loop() {

  lightUp(intdiv(count, FPS_PER_FRAME));
  count++;
  if (count == FPS_PER_FRAME * FRAMES_NUM) {

    count = 0;

  }

  delay(1000 / FPS);

}

