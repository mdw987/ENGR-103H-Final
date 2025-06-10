//All of the code in this file was written by me

#include <Adafruit_CircuitPlayground.h>

int reactionTime = 2000;
bool difficulty = false;
volatile bool switchFlag = false;
volatile bool leftButtonFlag = false;
volatile bool rightButtonFlag = false;
bool switchState;
bool pause = true;
bool buttonState = false;
bool leftButtonState = false;
bool rightButtonState = false;
int randomPixel;
int randomColor;
int randomDelay;
bool leftSide;
bool rightSide;
int counter = 0;

void setup() {
Serial.begin(9600);
CircuitPlayground.begin();
attachInterrupt(digitalPinToInterrupt(7),switchISR,CHANGE);
attachInterrupt(digitalPinToInterrupt(4),leftButtonISR,CHANGE);
attachInterrupt(digitalPinToInterrupt(5),rightButtonISR,CHANGE);
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

void happySound(){
  CircuitPlayground.playTone(800,150);
  CircuitPlayground.playTone(200,150);
  leftButtonFlag = false;
  rightButtonFlag = false;
  leftSide = false;
  rightSide = false;
  counter = counter+1;
}

void sadSound(){
  CircuitPlayground.playTone(200,175);
  CircuitPlayground.playTone(200,175);
  leftButtonFlag = false;
  rightButtonFlag = false;
  leftSide = false;
  rightSide = false;
  Serial.print("Game over. You score was ");
  Serial.println(counter);
  counter = 0;
  pause = true;
}

void loop() {

if(switchFlag == true){
  delay(5);
  switchState = digitalRead(7);
  if(switchState == HIGH){
    pause = false;
  }
  else{
    pause = true;
  }
  switchFlag = false;
}

if(pause == true){
  if(leftButtonFlag == true||rightButtonFlag == true){
    delay(5);
    leftButtonState = digitalRead(4);
    rightButtonState = digitalRead(5);
    if(leftButtonState == HIGH ||rightButtonState == HIGH){
      if(difficulty == false){
        difficulty = true;
        leftButtonFlag = false;
        rightButtonFlag = false;
        Serial.println("Hard Mode");
      }
      else{
        difficulty = false;
        leftButtonFlag = false;
        rightButtonFlag = false;
        Serial.println("Easy Mode");
      }
    }
  }
}

if(difficulty == false){
  reactionTime = 1500;
}
else{
  reactionTime = 500;
}

if(pause == false){
    randomPixel = random(0,10);
    randomColor = random(0,2);
    if(randomColor == 0){
      CircuitPlayground.setPixelColor(randomPixel,255,0,0);
    }
    else{
      CircuitPlayground.setPixelColor(randomPixel,0,255,0);
    }
    delay(reactionTime);
  if(randomPixel <= 4){
    leftSide = true;
  }
  else if(randomPixel >= 5){
    rightSide = true;
    leftSide = false;
  }
    CircuitPlayground.clearPixels();
  if(leftSide == true){
    if(randomColor == 0){
      if(leftButtonFlag == true && rightButtonFlag == false){
        sadSound();
      }
      else if(rightButtonFlag == true && leftButtonFlag == false){
        happySound();
      }
      else if(rightButtonFlag == true && leftButtonFlag == true){
        sadSound();
      }
      else if(rightButtonFlag == false && leftButtonFlag == false){
        sadSound();
      }
    }
    else if(randomColor == 1){
      if(leftButtonFlag == true && rightButtonFlag == false){
        happySound();
      }
      else if(rightButtonFlag == true && leftButtonFlag == false){
        sadSound();
      }
      else if(rightButtonFlag == true && leftButtonFlag == true){
       sadSound();
      }
      else if(rightButtonFlag == false && leftButtonFlag == false){
        sadSound();
      }
    }
  }
  if(rightSide == true){
    if(randomColor == 0){
      if(leftButtonFlag == true && rightButtonFlag == false){
        happySound();
      }
      else if(rightButtonFlag == true && leftButtonFlag == false){
        sadSound();
      }
      else if(rightButtonFlag == true && leftButtonFlag == true){
        sadSound();
      }
      else if(rightButtonFlag == false && leftButtonFlag == false){
        sadSound();
      }
    }
    else if(randomColor == 1){
      if(leftButtonFlag == true && rightButtonFlag == false){
        sadSound();
      }
      else if(rightButtonFlag == true && leftButtonFlag == false){
        happySound();
      }
      else if(rightButtonFlag == true && leftButtonFlag == true){
        sadSound();
      }
      else if(rightButtonFlag == false && leftButtonFlag == false){
        sadSound();
      }
    }
  }
}
}