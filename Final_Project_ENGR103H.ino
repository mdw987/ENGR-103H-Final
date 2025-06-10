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
 
void switchISR(){ // This ISR activates when the switch moves
  switchFlag = true;
} 

void leftButtonISR(){ // This ISR activates when the left button moves
  leftButtonFlag = true;
}

void rightButtonISR(){ // This ISR activates when the right button moves
  rightButtonFlag = true;
}

void happySound(){ // This function plays when you successfully react.
  CircuitPlayground.playTone(800,150);
  CircuitPlayground.playTone(200,150); // Happy tune
  leftButtonFlag = false;
  rightButtonFlag = false;
  leftSide = false;
  rightSide = false; // Reset all boolean values to false for next reaction.
  counter = counter+1; // Increases score by one
} 

void sadSound(){ // This function plays when you fail to react.
  CircuitPlayground.playTone(200,175); 
  CircuitPlayground.playTone(200,175); // Sad tune
  leftButtonFlag = false;
  rightButtonFlag = false;
  leftSide = false;
  rightSide = false; // Reset all boolean values to false for next game.
  Serial.print("Game over. You score was ");
  Serial.println(counter); // Prints your score for you to read in serial monitor.
  counter = 0; // Resets score for next game.
  pause = true; // Pauses game.
}

void loop() {

if(switchFlag == true){
  delay(5);
  switchState = digitalRead(7);
  if(switchState == HIGH){
    pause = false; // If the switch is to the left, and it has moves, the game will not be paused.
  }
  else{
    pause = true; // If the switch is to the right, or it has not been moved, the game will be paused.
  }
  switchFlag = false; // Resets switch ISR flag
}

if(pause == true){ // This section of code just says that if either button is pressed when the game is paused, the difficulty will change.
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
  reactionTime = 1500; // If it is easy mode, you will have 1.5 seconds to react.
}
else{
  reactionTime = 500; // If it is hard mode, you will have 0.5 seconds to react.
}

if(pause == false){ // This section of code is the actual game.
    randomPixel = random(0,10);
    randomColor = random(0,2);
    if(randomColor == 0){
      CircuitPlayground.setPixelColor(randomPixel,255,0,0); 
    }
    else{
      CircuitPlayground.setPixelColor(randomPixel,0,255,0);
    } /*The above lines of code create a 50% chance that the light will be green, and a 50% chance that the light will be red. If random color is zero, the light will be red.
         If random color is one, the light will be green. The pixel that is lit up is also random.*/
    delay(reactionTime); // The delay that defines the difficuly of the game is here.
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
        sadSound(); // If the light was on the left and was red, and you pressed only the left button, you fail.
      }
      else if(rightButtonFlag == true && leftButtonFlag == false){
        happySound(); // If the light was on the left and was red, and you pressed only the right button, you succeed.
      }
      else if(rightButtonFlag == true && leftButtonFlag == true){
        sadSound(); // If the light was on the left and was red, and you pressed both buttons you fail.
      }
      else if(rightButtonFlag == false && leftButtonFlag == false){
        sadSound(); // If the light was on the left and was red, and you didn't press any buttons you fail.
      }
    }
    else if(randomColor == 1){ //If you 
      if(leftButtonFlag == true && rightButtonFlag == false){
        happySound(); // If the light was on the left and was green, and you pressed only the left button, you succeed.
      }
      else if(rightButtonFlag == true && leftButtonFlag == false){
        sadSound(); // If the light was on the left and was green, and you pressed only the right button, you fail.
      }
      else if(rightButtonFlag == true && leftButtonFlag == true){
       sadSound(); // If the light was on the left and was green, and you pressed both buttons, you fail.
      }
      else if(rightButtonFlag == false && leftButtonFlag == false){
        sadSound(); // If the light was on the left and was green, and you pressed neither buttons, you fail.
      }
    }
  } // Extrapolate the above comments below to the section of the code if a light on the right was lit up.
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
