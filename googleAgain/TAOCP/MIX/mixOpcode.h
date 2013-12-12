#ifndef _MIX_OPCODE_H
#define _MIX_OPCODE_H   


namespace MIX{
  enum OpCode
    {
      NOP = 0,
      ADD = 1,
      SUB = 2,
      MUL = 3,
      DIV = 4,
  
      MOVE = 7,

      LDA = 8,
      LDX = 15,
      LDAN = 16,
      LDXN = 23,

      STA = 24,
      STX = 31,
      STJ = 32,
      STZ = 33,

      JBUS = 34,
      IOC = 35,
      IN = 36,
      OUT = 37,
      JRED = 38,

      CMPA = 56,
      CMPX = 63,

      // extension opcode which need both C+F 
      // to determine final Operation
      LDI = 64, // 8+i
      LDIN, // 16+i
      STI, // 24+i
      ENTA, // C=48, F=2
      ENTX, // C=55, F=2
      ENTI, // C=48+i, F=2
      ENNA, // C=48, F=3
      ENNX, // C=55, F=3,
      ENNI, // C=48+i, F=3;
      INCA, // C=48, F=0
      INCX, // C=55, F=0
      INCI, // C=48+i, F=0
      DECA, // C=48, F=1
      DECX, // C=55, F=1
      DECI, // C=48+i, F=1
      CMPI, // C=56+i
      JMP,  // C=39, F=0
      JSJ,  // C=39, F=1
      JOV,  // C=39, F=2
      JNOV, // C=39, F=3
      JL,   // C=39, F=4-9
      JE,  
      JG,
      JGE,
      JNE,
      JLE,

      JAN,  // C=40, F=0-5
      JAZ,
      JAP,
      JANN,
      JANZ,
      JANP,
      
      JXN,  // C=47, F=0-5
      JXZ,
      JXP,
      JXNN,
      JXNZ,
      JXNP,
      
      SLA,  // C=6, F=0-5
      SRA,
      SLAX,
      SRAX,
      SLC,
      SRC,

      HLT, // C=5, F=2
      NUM, // C=5, F=0
      CHAR, // C=5, F=1

      LASTOP
    };
}
#endif
