#include <Adafruit_NeoPixel.h>
#include <iostream>

#define MATRIX_X 32
#define MATRIX_Y 8
#define MATRIX_UNITS MATRIX_X * MATRIX_Y
#define FRAMES_NUM 4
#define MATRIX_PIN D4
#define FPS 8
#define FPS_PER_FRAME 1

#define COLORBIN1 0xA717D7
#define COLORBIN2 0xF4F4DF
#define COLORA 0x8BD3E6
#define COLORB 0xF6EB61
#define COLORC 0x000000

const String mtxinput = 
"0000 0000 0000 0000 0000 0000 0000 0000 " 
"0000 0002 2000 2200 0220 0222 0000 0000 "
"0000 0A02 0202 0020 2000 0200 0A00 0000 "
"00AA A002 2002 0020 0220 0222 00AA A000 "
"0000 0A02 0202 0020 0002 0200 0A00 0000 "
"00B0 0002 0200 2200 0220 0222 000B 0B00 "
"0B0B 0000 0000 0000 0000 0000 0000 B000 "
"0000 000A 0A0A 0A0A 0A0A 0A0A 0000 0000 "

"0000 0000 0000 0000 0000 0000 0000 0000 " 
"0000 0002 2000 2200 0220 0222 0000 0000 "
"0000 0A02 0202 0020 2000 0200 0A00 0000 "
"00AA A002 2002 0020 0220 0222 00AA A000 "
"0000 0A02 0202 0020 0002 0200 0A00 0000 "
"00B0 0002 0200 2200 0220 0222 000B 0B00 "
"0B0B 0000 0000 0000 0000 0000 0000 B000 "
"0000 0000 A0A0 A0A0 A0A0 A0A0 0000 0000 "

"0000 0000 0000 0000 0000 0000 0000 0000 " 
"0000 0002 2000 2200 0220 0222 0000 0000 "
"0000 0A02 0202 0020 2000 0200 0A00 0000 "
"00AA A002 2002 0020 0220 0222 00AA A000 "
"0000 0A02 0202 0020 0002 0200 0A00 0000 "
"0B0B 0002 0200 2200 0220 0222 0000 B000 "
"00B0 0000 0000 0000 0000 0000 000B 0B00 "
"0000 000A 0A0A 0A0A 0A0A 0A0A 0000 0000 "

"0000 0000 0000 0000 0000 0000 0000 0000 " 
"0000 0002 2000 2200 0220 0222 0000 0000 "
"0000 0A02 0202 0020 2000 0200 0A00 0000 "
"00AA A002 2002 0020 0220 0222 00AA A000 "
"0000 0A02 0202 0020 0002 0200 0A00 0000 "
"0B0B 0002 0200 2200 0220 0222 0000 B000 "
"00B0 0000 0000 0000 0000 0000 000B 0B00 "
"0000 0000 A0A0 A0A0 A0A0 A0A0 0000 0000 ";
 
char ledmatrix[FRAMES_NUM][MATRIX_UNITS];
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

    ledmatrix[frameIndex][pixelIndex] = c;

    pixelIndex++;

  }

  matrix.begin();
  matrix.setBrightness(40);
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

    char matval = ledmatrix[frame][i];
    uint32_t color = 0;
    switch (matval) {
      case '0': color = 0x000000; break;
      case '1': color = 0xFFFFFF; break;
      case '2': color = rand() % 2 ? COLORBIN1 : COLORBIN2; break;
      case 'A': color = COLORA; break;
      case 'B': color = COLORB; break;
      case 'C': color = COLORC; break;
    }
    matrix.setPixelColor(matrixRotate(i), color);

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

