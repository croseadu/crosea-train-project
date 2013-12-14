#ifndef _MIX
#define _MIX
#include "mixRegType.h"
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
  class TapeUnit;

  class MixMachine
  {
    AReg rA;
    XReg rX;
    IReg rI[6];
    JReg rJ;

    bool overflowToggle;
    enum CompareResult{
      None,
      Equal,
      Greater,
      Less,
    };
    CompareResult compareIndicator;
    
    class MemoryCell 
    {
      GeneralReg m[4000];
    public:
      const GeneralReg read(int address) const
      {
	return m[address];
      }
      void write(int address, const GeneralReg &src, unsigned char field) 
      {
	unsigned char left = field/8, right=field%8;
	if (left == 0) {
	  m[address].setSign(src.getSign());
	  ++left;
	}
	unsigned int srcIdx = 4;
	while(right >= left) {
	  m[address].setByte(src.getByte(srcIdx), right-1);
	  --srcIdx;
	  --right;
	}
      }
    };
    MemoryCell mem;

    TapeUnit *unitBuffer;

    //ProgramCounter;
    unsigned int pc;
    bool isHalt;

    const MixISAInfo &isaInfo;
    void init();
    MixMachine();

#define HANDLE_INST(num, opcode, Class)		\
    void visit##opcode(const Class &);
#include "Instruction.def"
#undef HANDLE_INST
  public:
    void run(const char *pProgram);
    static MixMachine & getMixMachine() 
    {
      static MixMachine mixMachine;
      return mixMachine;
    }
  };


   
}//end of namespace Mix
#endif _MIX
