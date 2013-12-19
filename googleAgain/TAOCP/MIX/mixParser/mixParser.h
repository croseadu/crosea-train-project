#ifndef _MIX_PARSER_H
#define _MIX_PARSER_H
#include "../include/mixInst.h"
#include "mixLexer.h"

class MixParser
{
  class InstInfo
  {
    enum Opcode op;
    int address;
    int idxRegID;
    int field;
    std::string loc;
    std::string jumpTarget;
  };
  parseComments();
  parseExpr();
  parseInstruction();

  const Instruction * buildInstruction();
  
 public:
  
  parseProgram();
};

#endif
