#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <iostream>

#define MATRIX_X 32 //width of the matrix
#define MATRIX_Y 8 //height of the matrix
#define MATRIX_UNITS MATRIX_X * MATRIX_Y
#define MATRIX_PIN D4 //pin of the matrix

#define PLAYER_PIN_RX 3
#define PLAYER_PIN_TX 1

#define FRAMES_NUM 8 //number of frames
#define FPS 6 //speed of the animation in Frames Per Second
#define FPS_PER_FRAME_RATIO 1 //ratio between fps and frame duration; 1 is exactly fps, 2 is 2 times fps, etc; bigger or equal 1 (useful for asynchronous effects during the animation)
#define CYCLEDURATION (FPS_PER_FRAME_RATIO * FRAMES_NUM) / FPS //duration of one animation cycle in seconds

#define COLORBIN1 0xA717D7 //first color of a binary led
#define COLORBIN2 0xF4F4DF //second color of a binary led
#define COLORA 0x8BD3E6 //color of A-led
#define COLORB 0xF6EB61 //color of B-led
#define COLORC 0x000000 //color of C-led

const String mtxinput = 
"0000 0000 0000 0000 0000 0000 0000 0000 " 
"0000 0002 2000 2200 0220 0222 0000 0000 "
"0000 0A02 0202 0020 2000 0200 0A00 0000 "
"00AA A002 2002 0020 0220 0222 00AA A000 "
"0000 0A02 0202 0020 0002 0200 0A00 0000 "
"B0B0 0002 0200 2200 0220 0222 000B 0B00 "
"0B0B 0000 0000 0000 0000 0000 0000 B0B0 "
"0000 000A 0A0A 0A0A 0A0A 0A0A 0000 0000 "

"0000 0000 0000 0000 0000 0000 0000 0000 " 
"0000 0002 2000 2200 0220 0222 0000 0000 "
"0000 0A02 0202 0020 2000 0200 0A00 0000 "
"00AA A002 2002 0020 0220 0222 00AA A000 "
"0000 0A02 0202 0020 0002 0200 0A00 0000 "
"B0B0 0002 0200 2200 0220 0222 000B 0B00 "
"0B0B 0000 0000 0000 0000 0000 0000 B0B0 "
"0000 0000 A0A0 A0A0 A0A0 A0A0 0000 0000 "

"0000 0000 0000 0000 0000 0000 0000 0000 " 
"0000 0002 2000 2200 0220 0222 0000 0000 "
"0000 0A02 0202 0020 2000 0200 0A00 0000 "
"00AA A002 2002 0020 0220 0222 00AA A000 "
"0000 0A02 0202 0020 0002 0200 0A00 0000 "
"B0B0 0002 0200 2200 0220 0222 000B 0B00 "
"0B0B 0000 0000 0000 0000 0000 0000 B0B0 "
"0000 000A 0A0A 0A0A 0A0A 0A0A 0000 0000 "

"0000 0000 0000 0000 0000 0000 0000 0000 " 
"0000 0002 2000 2200 0220 0222 0000 0000 "
"0000 0A02 0202 0020 2000 0200 0A00 0000 "
"00AA A002 2002 0020 0220 0222 00AA A000 "
"0000 0A02 0202 0020 0002 0200 0A00 0000 "
"B0B0 0002 0200 2200 0220 0222 000B 0B00 "
"0B0B 0000 0000 0000 0000 0000 0000 B0B0 "
"0000 0000 A0A0 A0A0 A0A0 A0A0 0000 0000 "

"0000 0000 0000 0000 0000 0000 0000 0000 " 
"0000 0002 2000 2200 0220 0222 0000 0000 "
"0000 0A02 0202 0020 2000 0200 0A00 0000 "
"00AA A002 2002 0020 0220 0222 00AA A000 "
"0000 0A02 0202 0020 0002 0200 0A00 0000 "
"0B0B 0002 0200 2200 0220 0222 0000 B0B0 "
"B0B0 0000 0000 0000 0000 0000 000B 0B00 "
"0000 000A 0A0A 0A0A 0A0A 0A0A 0000 0000 "

"0000 0000 0000 0000 0000 0000 0000 0000 " 
"0000 0002 2000 2200 0220 0222 0000 0000 "
"0000 0A02 0202 0020 2000 0200 0A00 0000 "
"00AA A002 2002 0020 0220 0222 00AA A000 "
"0000 0A02 0202 0020 0002 0200 0A00 0000 "
"0B0B 0002 0200 2200 0220 0222 0000 B0B0 "
"B0B0 0000 0000 0000 0000 0000 000B 0B00 "
"0000 0000 A0A0 A0A0 A0A0 A0A0 0000 0000 "

"0000 0000 0000 0000 0000 0000 0000 0000 " 
"0000 0002 2000 2200 0220 0222 0000 0000 "
"0000 0A02 0202 0020 2000 0200 0A00 0000 "
"00AA A002 2002 0020 0220 0222 00AA A000 "
"0000 0A02 0202 0020 0002 0200 0A00 0000 "
"0B0B 0002 0200 2200 0220 0222 0000 B0B0 "
"B0B0 0000 0000 0000 0000 0000 000B 0B00 "
"0000 000A 0A0A 0A0A 0A0A 0A0A 0000 0000 "

"0000 0000 0000 0000 0000 0000 0000 0000 " 
"0000 0002 2000 2200 0220 0222 0000 0000 "
"0000 0A02 0202 0020 2000 0200 0A00 0000 "
"00AA A002 2002 0020 0220 0222 00AA A000 "
"0000 0A02 0202 0020 0002 0200 0A00 0000 "
"0B0B 0002 0200 2200 0220 0222 0000 B0B0 "
"B0B0 0000 0000 0000 0000 0000 000B 0B00 "
"0000 0000 A0A0 A0A0 A0A0 A0A0 0000 0000 ";
 
char ledmatrix[FRAMES_NUM][MATRIX_UNITS];
Adafruit_NeoPixel matrix(MATRIX_UNITS, MATRIX_PIN, NEO_GRB + NEO_KHZ800);
SoftwareSerial playerSerial(PLAYER_PIN_RX, PLAYER_PIN_TX);
DFRobotDFPlayerMini player;
int count = 0;
double elapsedTime = 0;

void setup() {

  Serial.begin(9600);
  playerSerial.begin(9600);
  
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
  matrix.setBrightness(0);
  matrix.show();

  player.volume(5);
  player.play(1);

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

void doFrame() {
  lightUp(intdiv(count, FPS_PER_FRAME_RATIO));
}

int clamp(int value, int min, int max) {
  return value > max ? max : value < min ? min : value;
}

void animation() {

  if (elapsedTime >= 5) {

    if (elapsedTime >= 10) {
      matrix.setBrightness(clamp(matrix.getBrightness() - 5, 0, 60));
      player.volume(clamp(player.readVolume() - 2, 0, 30);
    } else {
      matrix.setBrightness(clamp(matrix.getBrightness() + 5, 0, 60));
      player.volume(clamp(player.readVolume() + 2, 0, 30);
    }

    doFrame();

  } else {

    matrix.clear();
    matrix.show();

  }

}

void loop() {

  animation();

  elapsedTime += (1000 / FPS) * 0.001f;

  count++;
  if (count == FPS_PER_FRAME_RATIO * FRAMES_NUM) {

    count = 0;

  }

  delay(1000 / FPS);

}

