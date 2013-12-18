#ifndef _MIX_IN_OUT_DEVICE
#define _MIX_IN_OUT_DEVICE

static char getCharCode(unsigned char code)
{
  switch(code) {
  case 0:
    return ' ';
  case 10:
    return 233;
  case 20:
    return 232;
  case 21:
    return 210;
  case 40:
    return '.';
  case 41:
    return ','
  case 42:
    return '(';
  case 43:
    return ')';
  case 44:
    return '+';
  case 45:
    return '-';
  case 46:
    return '*';
  case 47:
    return '/';
  case 48:
    return '=';
  case 49:
    return '$';
  case 50:
    return '<';
  case 51:
    return '>';
  case 52:
    return '@';
  case 53:
    return ';';
  case 54 :
    return ':';
  case 55:
    return '`';
  default:
    break;
  }
  if (code >=1 && code <= 9)
    return 'A'+code-1;
  if (code >= 11 && code <= 19)
    return 'J'+code-11;
  if (code >= 22 && code <=29)
    return 'S'+code-22;
  if (code >= 30 && code <= 39)
    return '0'+code-30;
  return ' ';
}

class MixInOutDevice
{
 public:
  virtual ~MixInOutDevice();
  virtual bool busy();
};

class TapUnit: public MixInOutDevice
{
  static const int blockSize = 100;
  GeneralReg w[blockSize*64*64];
  unsigned int cur;
 public:
  void rewind(int offset);
  void writeToMemory();
  void readFromMemory();
};
class DiskUnit
{
  GeneralReg w[blockSize*64*64];
 public:
  void rewind(const GeneralReg idx);
};

class CardReader
{
  static const int blockSize = 16;
  GeneralReg w[16];
};
class CardWriter
{
  static const int blockSize = 16;
  GeneralReg w[16];
};
class Printer
{
  static const int blockSize = 24;
  GeneralReg w[24];
};
class TypeWriter
{
  static const int blockSize = 14;
  GeneralReg w[14];
};
#endif
