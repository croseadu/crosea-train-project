#include "mixInst.h"
#include <string>
using std::string;

namespace MIX
{

  // OP ADDRESS ,I(F)
  // Omit ,I if I == 0;
  // Omit (F) if F is a standard Filed(0:5)

  const std::string Instruction::print()
  {
    MixISAInfo isaInfo = MixISAInfo::getISAInfo();
    unsigned char majorOp = inst.getMajorOpcode();
    unsigned char minorOp = inst.getMinorOpcode();
    bool hasMinorOpcode = isaInfo.hasMinorOpcode(majorOp);
    enum Opcode opcode = isaInfo.getOpcode(majorOp, minorOp);
    string opName = isaInfo.getNameViaOpcode(opcode);
    string output;

    output<<OpName<<" ";
    output<<getAddress;
    if ((unsigned int Idx = getIndexRegID()) != 0)
      output<<","<<Idx;
    if (!hasMinorOpcode && field != 5)
      output<<"("<<field<<")";
    output<<std::endl;
    return output;
  }


  ostream & operator<<(ostream &out, const Instruction &inst)
  {
    out<<inst.print();
    return out;
  }


}
