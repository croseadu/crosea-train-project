#ifndef _MIX_REG_H
#define _MIX_REG_H

#include <assert>

namespace MIX {
  class MixByte
  {
    unsigned char value :6;
    unsigned char reserved :2;
  public:
    MixByte():value(0), reserved(0) {}
    void reset()
    {
      value = 0;
      reserved = 0;
    }
    unsigned char read() const { return value; }
    unsigned char write(unsigned char inVal)  
    { 
      assert(inVal < 64);
      value = inVal; 
    }
  };

  class GeneralReg
  {
    MixByte data[5];
    bool negative;
  public:
    GeneralReg():negative(false){}
    void reset()
    {
      for(int i = 0; i < 5; ++i)
	data[i].reset;
      negative = false;
    }
    int read(unsigned char field) 
    {
      int L;
      int R;
      int sign = 1;
      int result;
      L = field/8;
      R = field%8;
      if (L == 0) {
	sign = nagative?-1:1;
	++L;
      }
      while (L <= R) {
	result *= 64;
	result += data[L-1].read();
	++L;
      }
      return result*sign;
    }
    void getSign() const { return negative; }
    void setSign(bool neg) { negative = neg; }
    void setByte(const MixByte &src, unsigned int idx) { data[idx] = src; }
  };

  typedef GeneralReg AReg;
  typedef GeneralReg XReg;

  class IReg
  {
    MixByte data[2];
    bool negative;
  public:
  IReg():negative(false) {}
    int read() const 
    { 
      int sign = negative:-1:1;
      int result = 64 * data[0].read()+data[1].read();
      return sign * result; 
    }
    void write(int inVal)
    {
      negative = inVal>0?1:-1;
      data[0].write(inVal/64);
      data[1].write(inVal%64);
    }
  };

  class JReg
  {
    MixByte data[2];
  };
}
#endif