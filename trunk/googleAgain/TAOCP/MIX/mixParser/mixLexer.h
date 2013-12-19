#ifndef _MIX_LEXER_H
#define _MIX_LEXER_H

#include <map>
#include <vector>

enum MixKeyword {
#define HANDLE_INST(num, opcode, Class) \
  KW_##opcode,
#include "../include/Instruction.def"
#undefine HANDLE_INST
  KW_LAST
};

enum MixKeyword getKeyword()
{
  
}

enum TokenKind {
  OPCODE_KIND,
  INTEGER_KIND,
  LOC_KIND,
  CONSTANT_KIND,
  COMMA_KIND,
  LEFTBRACE_KIND,
  RIGHTBRACE_KIND,
  AOP_KIND,
  CONSTDEF_KIND,
};

class Token
{
  enum TokenKind m_kind;
  void *data;
 public:
  Token *createToken(enum TokenKind kind, const std::string &in);
  ~Token()
  {
    delete data;
  }
};
class MixLexer
{
  static int evalueExpr(const std::vector<Token> &expr);
  std::map<std::string, enum MixKeyword> tokenToKeyword;
  std::map<std::string, int> constValPool;
  std::map<std::string, std::vector<unsigned int> > labelPool;
  std::map<unsigned int, std::string> literalPool;
  MixLexer();
 public:
  static MixLexer & getLexer() 
  {
    static MixLexer mixLexer;
    return mixLexer;
  }  
  
}

#endif
