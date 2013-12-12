
#include "mixRegType.h"
#include "mixOpcode.h"
#include <string>
#include <iostream>
// byte only have 6 bits
// represent 0-63
namespace MIX {


  // overflow toggle

  // Comparison indicator E G L

  // Memory cells 4000 words
  
  // Manetic tape units Disk and drums

  // Instruction Format
  // OP ADDRESS, I(F)
  class MixMachine;
  Class Instruction
  {
    struct _Address {
      bool negative;
      MixByte A[2];
    }addr; // +-AA
    MixByte indexReg;// I
    MixByte field;//F
    MixByte opcode; //C

    unsigned char getMajorOpcode() const { return opcode.read();}
    unsigned char getMinorOpcode() const { return field.read();}
    int getAddress() const 
    {
      int sign = negative?1:-1;
      int result = 64*A[0].read()+A[1].read;
      return sign*result;
    }
    unsigned int getIndexRegID() const
    {
      return indexReg.read();
    }

  public:
    const std::string print();
    void execute(MixMachine &);

  };

  ostream & operator<<(ostream &out, const Instruction &inst)
}
