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
    IReg rI[5];
    JReg rJ;

    bool overflowToggle;
    enum CompareResult{
      None,
      Equal,
      Greater,
      Less,
    };
    CompareResult compareIndicator;
    
    GeneralReg memoryCell[4000];

    TapeUnit *unitBuffer;

    //ProgramCounter;
    unsigned int pc;

    void init();
    MixMachine();
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
