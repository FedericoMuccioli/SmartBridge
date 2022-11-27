#include "Arduino.h"
#include "LcdImpl.h"

LcdImpl::LcdImpl(int addr, int cols, int rows){
  lcd =  new LiquidCrystal_I2C(addr,cols,rows);
  lcd->init();
  lcd->backlight();
}

void LcdImpl::setCursor(int col, int row){
  lcd->setCursor(col,row);
}

void LcdImpl::print(const char c[]){
  lcd->print(c);
}
