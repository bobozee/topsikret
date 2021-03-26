#include <Adafruit_NeoPixel.h>
#include <iostream>

const String mtxinput = 
"0000 0000 0000 0000 0000 0000 0000 0000 " 
"0000 0001 1000 1100 0110 0111 0000 0000 "
"0000 0101 0101 0010 1000 0100 0100 0000 "
"0011 1001 1001 0010 0110 0111 0011 1000 "
"0000 0101 0101 0010 0001 0100 0100 0000 "
"0010 0001 0100 1100 0110 0111 0001 0100 "
"0101 0000 0000 0000 0000 0000 0000 1000 "
"0000 0000 0000 0000 0000 0000 0000 0000 "
"n "
"0000 0000 0000 0000 0000 0000 0000 0000 "
"0000 0001 1000 1100 0110 0111 0000 0000 "
"0000 0101 0101 0010 1000 0100 0100 0000 "
"0011 1001 1001 0010 0110 0111 0011 1000 "
"0000 0101 0101 0010 0001 0100 0100 0000 "
"0101 0001 0100 1100 0110 0111 0000 1000 "
"0010 0000 0000 0000 0000 0000 0001 0100 "
"0000 0000 0000 0000 0000 0000 0000 0000";
 
uint8_t ledmatrix[2][256];

void setup() {

  Serial.begin(9600);

  delay(250);

  String firstFrame;
  String secondFrame; 

  firstFrame = mtxinput;
  firstFrame.remove(320, 321);
  firstFrame.replace(" ", "");

  secondFrame = mtxinput.substring(320);
  secondFrame.replace(" ", "");
  secondFrame.remove(0, 1);

  for (int i = 0; i < 256; i++) {
    
    ledmatrix[0][i] = firstFrame.charAt(i);
    ledmatrix[1][i] = secondFrame.charAt(i);

  }

  

}

void loop() {
  // put your main code here, to run repeatedly:
}