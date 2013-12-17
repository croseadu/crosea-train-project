#include "mix.hpp"
#include <iostream>
#include <memory>

MixMachine::MixMachine():overflowToggle(false), 
			 compareIndicator(None),
			 unitBuffer(0),
			 isaInfo(MixISAInfo::getISAInfo())
{
  init();
}

void MixMachine::init()
{
  
}

void MixMachine::run(const char * pProgram)
{
  pc = 0;
  while (!isHalt) {
    Instruction inst(pProgram+5*pc);
    visit(inst);
  }

}

void MixMachine::visit(const Instruction &inst)
{
  unsigned char major = inst.getMajorOpcode();
  unsigned char minor = inst.getMinorOpcode();
  switch(isaInfo.getOpcode(major, minor)) {
#define HANDLE_INST(num, opcode, Class)		\
    case opcode: \
      visit##opcode(inst);
#include "Instruction.def"
#undef HANDLE_INST
  }
}

void MixMachine::visitNOP(const Instruction &inst)
{
  std::cout<<"visit NOP"<<std::endl;

}

void MixMachine::visitADD(const Instruction &inst)
{
  std::cout<<"visit ADD"<<std::endl;
  GeneralReg src;
  GeneralReg result;
  unsigned char field = inst.getField();
  if (field%8 == 6) {
    // FloatingPoint handle
    return;
  }

  bool overflow = false;
  loadHelper(inst, src, inst.getField());
  result = add(src, rA, &overflow);
  if (overflow) {

  } else if (result.isZero()) {

  }
  else {

  }
}
void MixMachine::visitSUB(const Instruction &inst)
{
  std::cout<<"visit SUB"<<std::endl;
  GeneralReg src;
  GeneralReg result;
  unsigned char field = inst.getField();
  if (field%8 == 6) {
    // FloatingPoint handle
    return;
  }

  bool overflow = false;
  loadHelper(inst, src, inst.getField());
  result = sub(src, rA, &overflow);
  if (overflow) {

  } else {

  }
}
void MixMachine::visitMUL(const Instruction &inst)
{
  std::cout<<"visit MUL"<<std::endl;
  GeneralReg src;
  GeneralReg result, result2;
  unsigned char field = inst.getField();
  if (field%8 == 6) {
    // FloatingPoint handle
    return;
  }

  loadHelper(inst, src, inst.getField());
  result = mul(src, rA, result2);
  rA = result;
  rX = resutl2;
}
void MixMachine::visitDIV(const Instruction &inst)
{
  std::cout<<"visit DIV"<<std::endl;
}

void MixMachine::visitMOVE(const Instruction &inst)
{
  std::cout<<"visit LDA"<<std::endl;
}

void MixMachine::loadHelper(const Instruction &inst, 
			    GeneralReg &dst,
			    bool flipSign)
{
  unsigned int field = inst.getField();
  GeneralReg content;
  int address = inst.getAddress();
  int idxReg = inst.getIndexRegID();
  if (idxReg > 0)
    address += rI[idxReg].read();

  content = mem.read(address);
  
  unsigned left = field/8, right = field%8;
  dst.reset();
  if (left == 0) { 
    dst.setSign(content.getSign());
    ++left;
  }
  int dstIdx = 4;
  while (right >= left) {
    dst.setByte(content.getByte(right-1), dstIdx);
    --right;
    --dstIdx;
  }  
  if (flipSign)
    dst.flipSign();
}
void MixMachine::visitLDA(const Instruction &inst)
{
  std::cout<<"visit LDA"<<std::endl;
  loadHelper(inst, rA);
}

void MixMachine::visitLDX(const Instruction &inst)
{
  std::cout<<"visit LDX"<<std::endl;
  loadHelper(inst, rX);
}

void MixMachine::visitLDAN(const Instruction &inst)
{
  std::cout<<"visit LDAN"<<std::endl;
  loadHelper(inst, rA, true);
}

void MixMachine::visitLDXN(const Instruction &inst)
{
  std::cout<<"visit LDXN"<<std::endl;
  loadHelper(inst, rX, true);
}

void MixMachine::visitSTA(const Instruction &inst)
{
  std::cout<<"visit STA"<<std::endl;
  int address = inst.getAddress();
  int idxReg = inst.getIndexRegID();
  if (idxReg > 0)
    address += rI[idxReg].read();

  mem.write(address, rA, inst.getField());
}
void MixMachine::visitSTX(const Instruction &inst)
{
  std::cout<<"visit STX"<<std::endl;
}
void MixMachine::visitSTJ(const Instruction &inst)
{
  std::cout<<"visit STJ"<<std::endl;
  int address = inst.getAddress();
  int idxReg = inst.getIndexRegID();
  if (idxReg > 0)
    address += rI[idxReg].read();
  mem.write(address, rJ,inst.getField());

}
void MixMachine::visitSTZ(const Instruction &inst)
{
  std::cout<<"visit STZ"<<std::endl;
  GeneralReg temp;
  temp.reset();
  int address = inst.getAddress();
  int idxReg = inst.getIndexRegID();
  if (idxReg > 0)
    address += rI[idxReg].read();
  mem.write(address, temp, inst.getField());
}


void MixMachine::visitJBUS(const Instruction &inst)
{
  std::cout<<"visit JBUS"<<std::endl;
}
void MixMachine::visitIOC(const Instruction &inst)
{
  std::cout<<"visit IOC"<<std::endl;
}
void MixMachine::visitIN(const Instruction &inst)
{
  std::cout<<"visit IN"<<std::endl;
}
void MixMachine::visitOUT(const Instruction &inst)
{
  std::cout<<"visit OUT"<<std::endl;
}
void MixMachine::visitJRED(const Instruction &inst)
{
  std::cout<<"visit JRED"<<std::endl;
}

void MixMachine::visitCMPA(const Instruction &inst)
{
  std::cout<<"visit CMPA"<<std::endl;
}
void MixMachine::visitCMPX(const Instruction &inst)
{
  std::cout<<"visit CMPX"<<std::endl;
}


void MixMachine::visitLDI(const Instruction &inst)
{
  std::cout<<"visit LDI"<<std::endl;
  
  loadHelper(inst, rI[inst.getMajorOpcode()-8]);
}
void MixMachine::visitLDIN(const Instruction &inst)
{
  std::cout<<"visit LDIN"<<std::endl;
  loadHelper(inst, rI[inst.getMajorOpcode()-16], true);
}
void MixMachine::visitSTI(const Instruction &inst)
{
  std::cout<<"visit STI"<<std::endl;
  int address = inst.getAddress();
  int idxReg = inst.getIndexRegID();
  if (idxReg > 0)
    address += rI[idxReg].read();
  mem.write(address, rI[inst.getMajorOpcode()-24],inst.getField());
}

void MixMachine::visitENTA(const Instruction &inst)
{
  std::cout<<"visit ENTA"<<std::endl;
  rA.write(inst.getAddress);
}
void MixMachine::visitENTX(const Instruction &inst)
{
  std::cout<<"visit ENTX"<<std::endl;
  rX.write(inst.getAddress());
}
void MixMachine::visitENTI(const Instruction &inst)
{
  std::cout<<"visit ENTI"<<std::endl;
  rI[inst.getMajorOpcode()-48].write(inst.getAddress());
}

void MixMachine::visitENNA(const Instruction &inst)
{
  std::cout<<"visit ENNA"<<std::endl;
  rA.write(inst.getAddress());
  rA.flipSign();
}
void MixMachine::visitENNX(const Instruction &inst)
{
  std::cout<<"visit ENNX"<<std::endl;
  rX.write(inst.getAddress());
  rX.flipSign();
}
void MixMachine::visitENNI(const Instruction &inst)
{
  std::cout<<"visit ENNI"<<std::endl;
  rI[inst.getMajorOpcode()-48].write(inst.getAddress());
  rI[inst.getMajorOpcode()-48].flipSign();
}

void MixMachine::visitINCA(const Instruction &inst)
{
  std::cout<<"visit INCA"<<std::endl;
  GeneralReg temp(inst.getAddress());
  GeneralReg result;
  bool overflow = false;
  result = add(rA, temp, overflow);
}
void MixMachine::visitINCX(const Instruction &inst)
{
  std::cout<<"visit INCX"<<std::endl;
  GeneralReg temp(inst.getAddress());
  GeneralReg result;
  bool overflow = false;
  result = add(rX, temp, overflow);
}
void MixMachine::visitINCI(const Instruction &inst)
{
  std::cout<<"visit INCI"<<std::endl;
  
}

void MixMachine::visitDECA(const Instruction &inst)
{
  std::cout<<"visit DECA"<<std::endl;
}
void MixMachine::visitDECX(const Instruction &inst)
{
  std::cout<<"visit DECX"<<std::endl;
}
void MixMachine::visitDECI(const Instruction &inst)
{
  std::cout<<"visit DECI"<<std::endl;
}

void MixMachine::visitCMPI(const Instruction &inst)
{
  std::cout<<"visit CMPI"<<std::endl;
}

void MixMachine::visitJMP(const Instruction &inst)
{
  std::cout<<"visit JMP"<<std::endl;
}
void MixMachine::visitJSJ(const Instruction &inst)
{
  std::cout<<"visit JSJ"<<std::endl;
}
void MixMachine::visitJOV(const Instruction &inst)
{
  std::cout<<"visit JOV"<<std::endl;
}
void MixMachine::visitJNOV(const Instruction &inst)
{
  std::cout<<"visit JNOV"<<std::endl;
}

void MixMachine::visitJL(const Instruction &inst)
{
  std::cout<<"visit JL"<<std::endl;
}
void MixMachine::visitJE(const Instruction &inst)
{
  std::cout<<"visit JE"<<std::endl;
}
void MixMachine::visitJG(const Instruction &inst)
{
  std::cout<<"visit JG"<<std::endl;
}
void MixMachine::visitJGE(const Instruction &inst)
{
  std::cout<<"visit JGE"<<std::endl;
}
void MixMachine::visitJNE(const Instruction &inst)
{
  std::cout<<"visit JNE"<<std::endl;
}
void MixMachine::visitJLE(const Instruction &inst)
{
  std::cout<<"visit JLE"<<std::endl;
}

void MixMachine::visitJAN(const Instruction &inst)
{
  std::cout<<"visit JAN"<<std::endl;
}
void MixMachine::visitJAZ(const Instruction &inst)
{
  std::cout<<"visit JAZ"<<std::endl;
}
void MixMachine::visitJAP(const Instruction &inst)
{
  std::cout<<"visit JAP"<<std::endl;
}
void MixMachine::visitJANN(const Instruction &inst)
{
  std::cout<<"visit JANN"<<std::endl;
}
void MixMachine::visitJANZ(const Instruction &inst)
{
  std::cout<<"visit JANZ"<<std::endl;
}
void MixMachine::visitJANP(const Instruction &inst)
{
  std::cout<<"visit JANP"<<std::endl;
}


void MixMachine::visitJXN(const Instruction &inst)
{
  std::cout<<"visit JXN"<<std::endl;
}
void MixMachine::visitJXZ(const Instruction &inst)
{
  std::cout<<"visit JXZ"<<std::endl;
}
void MixMachine::visitJXP(const Instruction &inst)
{
  std::cout<<"visit JXP"<<std::endl;
}
void MixMachine::visitJXNN(const Instruction &inst)
{
  std::cout<<"visit JXNN"<<std::endl;
}
void MixMachine::visitJXNZ(const Instruction &inst)
{
  std::cout<<"visit JXNZ"<<std::endl;
}
void MixMachine::visitJXNP(const Instruction &inst)
{
  std::cout<<"visit JXNP"<<std::endl;
}

void MixMachine::visitSLA(const Instruction &inst)
{
  std::cout<<"visit SLA"<<std::endl;
}
void MixMachine::visitSRA(const Instruction &inst)
{
  std::cout<<"visit SRA"<<std::endl;
}
void MixMachine::visitSLAX(const Instruction &inst)
{
  std::cout<<"visit SLAX"<<std::endl;
}
void MixMachine::visitSRAX(const Instruction &inst)
{
  std::cout<<"visit SRAX"<<std::endl;
}
void MixMachine::visitSLC(const Instruction &inst)
{
  std::cout<<"visit SLC"<<std::endl;
}
void MixMachine::visitSRC(const Instruction &inst)
{
  std::cout<<"visit SRC"<<std::endl;
}

void MixMachine::visitHLT(const Instruction &inst)
{
  std::cout<<"visit HLT"<<std::endl;
  isHalt = true;
}
void MixMachine::visitNUM(const Instruction &inst)
{
  std::cout<<"visit NUM"<<std::endl;
}
void MixMachine::visitCHAR(const Instruction &inst)
{
  std::cout<<"visit CHAR"<<std::endl;
}
