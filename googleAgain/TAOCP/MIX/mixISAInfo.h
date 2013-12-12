#ifndef _MIX_ISA_INFO_H
#define _MIX_ISA_INFO_H
#include "mixOpcode.h"

#include <string>
#include <map>

namespace MIX
{
  class MixISAInfo
  {
    std::string opcodeName[LASTOP];
    std::map<std::string, enum Opcode> nameToOpcode;
    bool noMinorOpcode[64];
    MixISAInfo();
    initOpcodeInfo();
    initOpcodeName();
    initOpcodeMap(); 
    static const MixISAInfo &getMixISAInfo();
  public:
    
    static const MixISAInfo & getISAInfo();
    enum Opcode getOpcode(unsigned char, unsigned char);
    enum Opcode getOpcodeViaName(const std::string &);
    const std::string & getNameViaOpcode(enum Opcode);
    bool hasMinorOpcode(unsigned char);
  };









}


#endif
