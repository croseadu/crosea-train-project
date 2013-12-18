#ifndef _MIX
#define _MIX
#include "mixRegType.h"
#include "mixInOutDevice.h"
#include <iostream>

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
      void write(int address, const IReg &src, unsigned char field) 
      {
	unsigned char left = field/8, right=field%8;
	m[address].reset();
	if (left == 0) {
	  m[address].setSign(src.getSign());
	  ++left;
	}
	unsigned int srcIdx = 4;
	while(right >= left) {
	  if (right > 3)
	    m[address].setByte(src.getByte(srcIdx), right-1);
	  --srcIdx;
	  --right;
	}
      }
      void write(int address, const JReg &src, unsigned char field) 
      {
	unsigned char left = field/8, right=field%8;
	m[address].reset();
	if (left == 0) {
	  m[address].setSign(false);
	  ++left;
	}
	unsigned int srcIdx = 2;
	while(right >= left) { 
	  m[address].setByte(src.getByte(srcIdx), right-1);
	  --srcIdx;
	  --right;
	}
      }

    };

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
    
    MemoryCell mem;

    InOutDevice *u[20];

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
    
    ~MixMachine();
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
