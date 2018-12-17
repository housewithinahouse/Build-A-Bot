// buttons don't really have a function yet. What do you want them to do? 

void checkButtons(){
  uint8_t buttons = lcd.readButtons();

  if (buttons) {
    lcd.clear();
    lcd.setCursor(0,0);
    if (buttons & BUTTON_UP) {
      lcd.print(F("UP "));
    }
    if (buttons & BUTTON_DOWN) {
      lcd.print(F("DOWN "));
    }
    if (buttons & BUTTON_LEFT) {
      lcd.print(F("LEFT "));
    }
    if (buttons & BUTTON_RIGHT) {
      lcd.print(F("RIGHT "));
    }
    if (buttons & BUTTON_SELECT) {
      lcd.print(F("SELECT "));
    }
  }
}

  
