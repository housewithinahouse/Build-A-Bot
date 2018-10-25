void LEDMatrixShow(){
  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(LED_ON);
  
  if(currentMillis-previousMatrixMillis>=matrixAnimationInterval){

    previousMatrixMillis = currentMillis;
    matrix.clear();
    matrix.setCursor(matrixCursorPos,0);
    matrix.print(F("Build A Bot"));
    matrix.writeDisplay();
    matrixCursorPos--;
    if(matrixCursorPos<=-70){
      matrixCursorPos=20;
    }
  }
}

//I don't know if we have enough memory to fit all of this in. We might just be out of room...lol. Never done that before! 
