#ifndef __LCD__
#define __LCD__

class Lcd {
public:
  virtual void setCursor(int col, int row) = 0;   
  virtual void print(const char c[]) = 0;  
};

#endif
