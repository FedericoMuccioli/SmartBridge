#ifndef __LCDIMPL__
#define __LCDIMPL__

#include "Lcd.h"
#include <LiquidCrystal_I2C.h>

class LcdImpl: public Lcd { 
public:
  LcdImpl(int addr, int cols, int rows);
  void setCursor(int col, int row);
  void print(const char c[]);
private:
  LiquidCrystal_I2C *lcd;
};

#endif

