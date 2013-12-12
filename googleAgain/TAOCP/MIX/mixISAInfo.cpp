#include "mixISAInfo.h"


namespace MIX
{

  MixISAInfo::initOpcodeInfo()
  {
    for (int i = 0; i < 64; ++i)
      noMinorOpcode[i] = true;

    noMinorOpcode[5] = false;
    noMinorOpcode[6] = false;
    
    for(int i = 9; i < 15; ++i)
      noMinorOpcode[i] = false;

    for(int i = 17; i < 23; ++i)
      noMinorOpcode[i] = false;
    
    for (int i = 25; i < 31; ++i)
      noMinorOpcode[i] = false;

    for (int i = 39; i < 56; ++i)
      noMinorOpcode[i] = false;
    for (int i = 57; i < 63; ++i)
      noMinorOpcode[i] = false;
  }
  MixISAInfo::initOpcodeName()
  {
#define INIT(s) \
    opcodeName[s] = #s
    INIT(NOP);
    INIT(ADD);
    INIT(SUB);
    INIT(MUL);
    INIT(DIV);
    INIT(MOVE);
    INIT(LDA);
    INIT(LDX);
    INIT(LDAN);
    INIT(LDXN);
    INIT(STA);
    INIT(STX);
    INIT(STJ);
    INIT(STZ);

    INIT(JBUS);
    INIT(IOC);
    INIT(IN);
    INIT(OUT);
    INIT(JRED);

    INIT(CMPA);
    INIT(CMPX);

    INIT(LDI);
    INIT(LDIN);
    INIT(STI);
    INIT(ENTA);
    INIT(ENTX);
    INIT(ENTI);
    INIT(ENNA);
    INIT(ENNX);
    INIT(ENNI);

    INIT(INCA);
    INIT(INCX);
    INIT(INCI);

    INIT(DECA);
    INIT(DECX);
    INIT(DECI);
    
    INIT(CMPI);
    INIT(JMP);
    INIT(JSJ);
    INIT(JOV);
    INIT(JNOV);

    INIT(JL);
    INIT(JE);
    INIT(JG);
    INIT(JGE);
    INIT(JNE);
    INIT(JLE);

    INIT(JAN);
    INIT(JAZ);
    INIT(JAP);
    INIT(JANN);
    INIT(JANZ);
    INIT(JANP);

    INIT(JXN);
    INIT(JXZ);
    INIT(JXP);
    INIT(JXNN);
    INIT(JXNZ);
    INIT(JXNP);

    INIT(SLA);
    INIT(SRA);
    INIT(SLAX);
    INIT(SRAX);
    INIT(SLC);
    INIT(SRC);
    
    INIT(HLT);
    INIT(NUM);
    INIT(CHAR);
     
  #undefine INIT  
  }
  MixISAInfo::initOpcodeMap()
  {
#define INIT(s) \
    nameToOpcode.insert(std::pair<std::string, enum Opcode>(#s, s))
    INIT(NOP);
    INIT(ADD);
    INIT(SUB);
    INIT(MUL);
    INIT(DIV);
    INIT(MOVE);
    INIT(LDA);
    INIT(LDX);
    INIT(LDAN);
    INIT(LDXN);
    INIT(STA);
    INIT(STX);
    INIT(STJ);
    INIT(STZ);

    INIT(JBUS);
    INIT(IOC);
    INIT(IN);
    INIT(OUT);
    INIT(JRED);

    INIT(CMPA);
    INIT(CMPX);

    INIT(LDI);
    INIT(LDIN);
    INIT(STI);
    INIT(ENTA);
    INIT(ENTX);
    INIT(ENTI);
    INIT(ENNA);
    INIT(ENNX);
    INIT(ENNI);

    INIT(INCA);
    INIT(INCX);
    INIT(INCI);

    INIT(DECA);
    INIT(DECX);
    INIT(DECI);
    
    INIT(CMPI);
    INIT(JMP);
    INIT(JSJ);
    INIT(JOV);
    INIT(JNOV);

    INIT(JL);
    INIT(JE);
    INIT(JG);
    INIT(JGE);
    INIT(JNE);
    INIT(JLE);

    INIT(JAN);
    INIT(JAZ);
    INIT(JAP);
    INIT(JANN);
    INIT(JANZ);
    INIT(JANP);

    INIT(JXN);
    INIT(JXZ);
    INIT(JXP);
    INIT(JXNN);
    INIT(JXNZ);
    INIT(JXNP);

    INIT(SLA);
    INIT(SRA);
    INIT(SLAX);
    INIT(SRAX);
    INIT(SLC);
    INIT(SRC);
    
    INIT(HLT);
    INIT(NUM);
    INIT(CHAR);
     
  #undefine INIT
  }

  MixISAInfo::MixISAInfo()
  {
    initOpcodeInfo();
    initOpcodeName();
    initOpcodeMap();   
  }

  const MixISAInfo &MixISAInfo::getISAInfo()
  {
    static MixISAInfo mixISAInfo;
    return mixISAInfo;
  }
  enum Opcode MixISAInfo::getOpcode(unsigned char major, unsigned int minor)
  {
    if (noMinorOpcode[major])
      return static_cast<enum Opcode>(major);
    
    // Complicated case

    return ...;
  }
  enum Opcode MixISAInfo::getOpcodeViaName(const std::string &name)
  {
    return nameToOpcode[name];
  }
  const std::string & MixISAInfo::getNameViaOpcode(enum Opcode opcode)
  {
    return opcodeName[opcode];
  }
  
}
