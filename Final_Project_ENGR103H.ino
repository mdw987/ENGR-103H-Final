#include <Adafruit_CircuitPlayground.h>

int gameCounter = 0;
volatile bool switchFlag = false;
volatile bool leftButtonFlag = false;
volatile bool rightButtonFlag = false;
bool switchState;
bool counterMode = true;
bool buttonState = false;
bool leftButtonState = false;
bool rightButtonState = false;
int randomPixel;
int randomColor;
int randomDelay;

void setup() {
Serial.begin(9600);
CircuitPlayground.begin();
attachInterrupt(digitalPinToInterrupt(7),switchISR,CHANGE);
attachInterrupt(digitalPinToInterrupt(4),leftButtonISR,FALLING);
attachInterrupt(digitalPinToInterrupt(5),rightButtonISR,FALLING);
}

void switchISR(){
  switchFlag = true;
}

void leftButtonISR(){
  leftButtonFlag = true;
}
void rightButtonISR(){
  rightButtonFlag = true;
}

void loop() {

if(switchFlag == true){
  delay(5);
  switchState = digitalRead(7);
  if(switchState == HIGH){
    counterMode = false;
  }
  else{
    counterMode = true;
  }
  switchFlag = false;
}

if(counterMode == true){
  if(leftButtonFlag == true||rightButtonFlag == true){
    delay(5);
    leftButtonState = digitalRead(4);
    rightButtonState = digitalRead(5);
    if(leftButtonState == LOW||rightButtonState == LOW){
      if(gameCounter == 0||gameCounter == 2){
        gameCounter = 1;
      }
      else{
        gameCounter = 2;
      }
    }
  }
  leftButtonFlag = false;
  rightButtonFlag = false;
}

if(counterMode == false){
  if(gameCounter == 1){
    randomPixel = random(0,10);
    randomColor = random(0,2);
    randomDelay = random(300,1000);
    delay(randomDelay);
    if(randomColor == 0){
      CircuitPlayground.setPixelColor(randomPixel,255,0,0);
    }
    else{
      CircuitPlayground.setPixelColor(randomPixel,0,255,0);
    }
    delay(500);
    CircuitPlayground.clearPixels();
  if(randomPixel == 0||1||2||3||4){
    if(randomColor == 0){
      if(leftButtonFlag == true){
        delay(5);
        leftButtonState = digitalRead(4);
        if(leftButtonState == LOW){
          CircuitPlayground.playTone(200,200);
        }
      }
      else if(rightButtonFlag == true){
        delay(5);
        rightButtonState = digitalRead(5);
        if(rightButtonState == LOW){
          CircuitPlayground.playTone(800,200);
        }
      }
      else if(leftButtonFlag == true && rightButtonFlag == true){
        delay(5);
        leftButtonState = digitalRead(4);
        rightButtonState = digitalRead(5);
        if(leftButtonState == HIGH && rightButtonState == HIGH){
          CircuitPlayground.playTone(200,200);
        }
      }
    }
    else if(randomColor == 1){
      if(leftButtonFlag == true){
        delay(5);
        leftButtonState = digitalRead(4);
        if(leftButtonState == LOW){
          CircuitPlayground.playTone(800,200);
        }
      }
      else if(rightButtonFlag == true){
        delay(5);
        rightButtonState = digitalRead(5);
        if(rightButtonState == LOW){
          CircuitPlayground.playtone(200,200);
        }
      }
      else if(leftButtonFlag == true && leftButtonFlag == true){
        CircuitPlayground.playTone(200,200);
      }
    }
  }
  if(randomPixel == 5||6||7||8||9){
    if(randomColor == 0){
      delay(5);
      leftButtonState = digitalRead(4);
      rightButtonState = digitalRead(5);
      if(leftButtonState == LOW){
        CircuitPlayground.playTone(800,200);
      }
      else if(rightButtonState == LOW){
        CircuitPlayground.playTone(200,200);
      }
      else if(leftButtonState == HIGH && leftButtonState == HIGH){
        CircuitPlayground.playTone(200,200);
      }
    }
    else if(randomColor == 1){
      delay(5);
      leftButtonState = digitalRead(4);
      rightButtonState = digitalRead(5);
      if(leftButtonState == LOW){
        CircuitPlayground.playTone(200,200);
      }
      else if(rightButtonState == LOW){
        CircuitPlayground.playTone(800,200);
      }
      else if(leftButtonState == HIGH && leftButtonState == HIGH){
        CircuitPlayground.playTone(200,200);
      }
    }
  }
  }
}
Serial.print("gameCounter is ");
Serial.println(gameCounter);
delay(500);
Serial.print("switchState is ");
Serial.println(switchState);
delay(500);
}
