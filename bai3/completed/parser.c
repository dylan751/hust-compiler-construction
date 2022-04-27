/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdlib.h>

#include "reader.h"
#include "scanner.h"
#include "parser.h"
#include "error.h"

Token *currentToken;
Token *lookAhead;

void scan(void) {
  Token* tmp = currentToken;
  currentToken = lookAhead;
  lookAhead = getValidToken();
  free(tmp);
}

void eat(TokenType tokenType) {
  if (lookAhead->tokenType == tokenType) {
    printToken(lookAhead);
    scan();
  } else missingToken(tokenType, lookAhead->lineNo, lookAhead->colNo);
}

// 01) Prog ::= KW_PROGRAM Ident SB_SEMICOLON Block SB_PERIOD
void compileProgram(void) {
  assert("Parsing a Program ....");
  eat(KW_PROGRAM);
  eat(TK_IDENT);
  eat(SB_SEMICOLON);
  compileBlock();
  eat(SB_PERIOD);
  assert("Program parsed!");
}

// 02) Block::= KW_CONST ConstDecl ConstDecls Block2
// 03) Block::= Block2
void compileBlock(void) {
  assert("Parsing a Block ....");
  if (lookAhead->tokenType == KW_CONST) {
    eat(KW_CONST);
    compileConstDecl();
    compileConstDecls();
    compileBlock2();
  } 
  else compileBlock2();
  assert("Block parsed!");
}

// 04) Block2 ::= KW_TYPE TypeDecl TypeDecls Block3
// 05) Block2 ::= Block3
void compileBlock2(void) {
  if (lookAhead->tokenType == KW_TYPE) {
    eat(KW_TYPE);
    compileTypeDecl();
    compileTypeDecls();
    compileBlock3();
  } 
  else compileBlock3();
}

// 06) Block3 ::= KW_VAR VarDecl VarDecls Block4
// 07) Block3 ::= Block4
void compileBlock3(void) {
  if (lookAhead->tokenType == KW_VAR) {
    eat(KW_VAR);
    compileVarDecl();
    compileVarDecls();
    compileBlock4();
  } 
  else compileBlock4();
}

// 08) Block4 ::= SubDecls Block5
void compileBlock4(void) {
  compileSubDecls();
  compileBlock5();
}

// 09) Block5 ::= KW_BEGIN Statements KW_END
void compileBlock5(void) {
  eat(KW_BEGIN);
  compileStatements();
  eat(KW_END);
}

// 10) ConstDecls::= ConstDecl ConstDecls
// 11) ConstDecls::= e (epsilon)
void compileConstDecls(void) {
  // TODO
  while(lookAhead->tokenType == TK_IDENT) {
    compileConstDecl();
    compileConstDecls();
  }
}

// 12) ConstDecl ::= Ident SB_EQUAL Constant SB_SEMICOLON
void compileConstDecl(void) {
  // TODO
  eat(TK_IDENT);
  eat(SB_EQ);
  compileConstant();
  eat(SB_SEMICOLON);
}

// 13) TypeDecls ::= TypeDecl TypeDecls
// 14) TypeDecls ::= 
void compileTypeDecls(void) {
  // TODO
  while(lookAhead->tokenType == TK_IDENT) {
    compileTypeDecl();
    compileTypeDecls();
  }
}

// 15) TypeDecl ::= Ident SB_EQUAL Type SB_SEMICOLON
void compileTypeDecl(void) {
  // TODO
  eat(TK_IDENT);
  eat(SB_EQ);
  compileType();
  eat(SB_SEMICOLON);
}

// 16) VarDecls::= VarDecl VarDecls
// 17) VarDecls::= 
void compileVarDecls(void) {
  // TODO
  while(lookAhead->tokenType == TK_IDENT){
    compileVarDecl();
    compileVarDecls();
  }
}

// 18) VarDecl ::= Ident SB_COLON Type SB_SEMICOLON
void compileVarDecl(void) {
  // TODO
  eat(TK_IDENT);
  eat(SB_COLON);
  compileType();
  eat(SB_SEMICOLON);
}

// 19) SubDecls::= FunDecl SubDecls
// 20) SubDecls::= ProcDecl SubDecls
// 21) SubDecls::= 
void compileSubDecls(void) {
  assert("Parsing subtoutines ....");
  // TODO
  if (lookAhead->tokenType == KW_FUNCTION) {
      compileFuncDecl();
      compileSubDecls();
  } else if (lookAhead->tokenType == KW_PROCEDURE) {
      compileProcDecl();
      compileSubDecls();
  }
  assert("Subtoutines parsed ....");
}

// 22) FunDecl ::= KW_FUNCTION Ident Params SB_COLON BasicType SB_SEMICOLON Block SB_SEMICOLON
void compileFuncDecl(void) {
  assert("Parsing a function ....");
  // TODO
  eat(KW_FUNCTION);
  eat(TK_IDENT);
  compileParams();
  eat(SB_COLON);
  compileBasicType();
  eat(SB_SEMICOLON);
  compileBlock();
  eat(SB_SEMICOLON);
  assert("Function parsed ....");
}


// 23) ProcDecl ::= KW_PROCEDURE Ident Params SB_SEMICOLON Block SB_SEMICOLON
void compileProcDecl(void) {
  assert("Parsing a procedure ....");
  // TODO
  eat(KW_PROCEDURE);
  eat(TK_IDENT);
  compileParams();
  eat(SB_SEMICOLON);
  compileBlock();
  eat(SB_SEMICOLON);
  assert("Procedure parsed ....");
}

// 24) Params ::= SB_LPAR Param Params2 SB_RPAR
// 25) Params ::= 
void compileParams(void) {
  // TODO
  switch (lookAhead->tokenType) {
  case SB_LPAR:
      eat(SB_LPAR);
      compileParam();
      compileParams2();
      eat(SB_RPAR);
      break;
  case SB_COLON:
  case SB_SEMICOLON:
      break;
  default:
      error(ERR_INVALIDPARAM, lookAhead->lineNo, lookAhead->colNo);
      break;
  }
}


// 26) Params2 ::= SB_SEMICOLON Param Params2
// 27) Params2 ::= 
void compileParams2(void) {
  // TODO
  switch (lookAhead->tokenType) {
  case SB_SEMICOLON:
      eat(SB_SEMICOLON);
      compileParam();
      compileParams2();
      break;
  case SB_RPAR:
      break;
  default:
      error(ERR_INVALIDPARAM, lookAhead->lineNo, lookAhead->colNo);
      break;
  }
}

// 28) Param::= Ident SB_COLON BasicType
// 29) Param::= KW_VAR Ident SB_COLON BasicType
void compileParam(void) {
  // TODO
  switch (lookAhead->tokenType) {
  case TK_IDENT:
      eat(TK_IDENT);
      eat(SB_COLON);
      compileBasicType();
      break;
  case KW_VAR:
      eat(KW_VAR);
      eat(TK_IDENT);
      eat(SB_COLON);
      compileBasicType();
      break;
  default:
      error(ERR_INVALIDPARAM, lookAhead->lineNo, lookAhead->colNo);
      break;
  }
}

// 30) Type ::= KW_INTEGER
// 31) Type ::= KW_CHAR
// 32) Type ::= TypeIdent
// 33) Type ::= KW_ARRAY SB_LSEL Number SB_RSEL KW_OF Type
void compileType(void) {
  // TODO
  switch(lookAhead->tokenType){
    case KW_INTEGER:
      eat(KW_INTEGER);
      break;
    case KW_CHAR:
      eat(KW_CHAR);
      break;
    case TK_IDENT:
      eat(TK_IDENT);
      break;
    case KW_ARRAY:
      eat(KW_ARRAY);
      eat(SB_LSEL);
      eat(TK_NUMBER);
      eat(SB_RSEL);
      eat(KW_OF);
      compileType();
      break;
    default:
      error(ERR_INVALIDTYPE, lookAhead->lineNo, lookAhead->colNo);
      break;
  }
}

// 34) BasicType ::= KW_INTEGER
// 35) BasicType ::= KW_CHAR
void compileBasicType(void) {
  // TODO
  switch(lookAhead->tokenType) {
    case KW_INTEGER:
      eat(KW_INTEGER);
      break;
    case KW_CHAR:
      eat(KW_CHAR);
      break;
    default:
      error(ERR_INVALIDTYPE, lookAhead->lineNo, lookAhead->colNo);
      break;
  }
}


// 36) UnsignedConstant ::= Number
// 37) UnsignedConstant ::= ConstIdent
// 38) UnsignedConstant ::= ConstChar
void compileUnsignedConstant(void) {
  // TODO
  switch(lookAhead->tokenType) {
    case TK_NUMBER:
      eat(TK_NUMBER);
      break;
    case TK_IDENT:
      eat(TK_IDENT);
      break;
    case TK_CHAR:
      eat(TK_CHAR);
      break;
    default:
      error(ERR_INVALIDCHARCONSTANT, lookAhead->lineNo, lookAhead->colNo);
      break;
  }
}

// 40) Consant ::= SB_PLUS Constant2
// 41) Consant ::= SB_MINUS Constant2
// 42) Consant ::= Constant2
// 43) Consant ::= ConstChar
void compileConstant(void) {
  // TODO
  switch(lookAhead->tokenType) {
    case SB_PLUS:
      eat(SB_PLUS);
      compileConstant2();
      break;
    case SB_MINUS:
      eat(SB_MINUS);
      compileConstant2();
      break;
    case TK_CHAR:
      eat(TK_CHAR);
      break;
    default:
      compileConstant2();
      break;
  }
}

// 44) Constant2::= ConstIdent
// 45) Constant2::= Number
void compileConstant2(void) {
  // TODO
  switch(lookAhead->tokenType) {
    case TK_IDENT:
      eat(TK_IDENT);
      break;
    case TK_NUMBER:
      eat(TK_NUMBER);
      break;
    default:
      error(ERR_INVALIDCONSTANT, lookAhead->lineNo, lookAhead->colNo);
      break;
  }
}


// 46) Statements ::= Statement Statements2
void compileStatements(void) {
  // TODO
  compileStatement();
  compileStatements2();
}

// 47) Statements2 ::= SB_SEMICOLON Statement Statement2
// 48) Statements2 ::= 
void compileStatements2(void) {
  // TODO
  switch (lookAhead->tokenType) {
  case SB_SEMICOLON:
      eat(SB_SEMICOLON);
      compileStatement();
      compileStatements2();
      break;
  // Follow
  case KW_END:
      break;
  // Error
  default:
      eat(SB_SEMICOLON);
      break;
  }
}

// 49) Statement ::= AssignSt
// 50) Statement ::= CallSt
// 51) Statement ::= GroupSt
// 52) Statement ::= IfSt
// 53) Statement ::= WhileSt
// 54) Statement ::= ForSt
// 55) Statement ::= 
void compileStatement(void) {
  switch (lookAhead->tokenType) {
  case TK_IDENT:
    compileAssignSt();
    break;
  case KW_CALL:
    compileCallSt();
    break;
  case KW_BEGIN:
    compileGroupSt();
    break;
  case KW_IF:
    compileIfSt();
    break;
  case KW_WHILE:
    compileWhileSt();
    break;
  case KW_FOR:
    compileForSt();
    break;
    // EmptySt needs to check FOLLOW tokens
  case SB_SEMICOLON:
    eat(SB_SEMICOLON);
    break;
  case KW_END:
  case KW_ELSE:
    break;
    // Error occurs
  default:
    error(ERR_INVALIDSTATEMENT, lookAhead->lineNo, lookAhead->colNo);
    break;
  }
}

// 56) AssignSt ::= Variable SB_ASSIGN Expession
// 57) AssignSt ::= FunctionIdent SB_ASSIGN Expression
void compileAssignSt(void) {
  assert("Parsing an assign statement ....");
  // TODO
  eat(TK_IDENT);
  if (lookAhead->tokenType == SB_LSEL) {
      compileIndexes();
  }
  eat(SB_ASSIGN);
  compileExpression();
  assert("Assign statement parsed ....");
}

// 58) CallSt ::= KW_CALL ProcedureIdent Arguments
void compileCallSt(void) {
  assert("Parsing a call statement ....");
  // TODO
  eat(KW_CALL);
  eat(TK_IDENT);
  compileArguments();
  assert("Call statement parsed ....");
}


// 59) GroupSt ::= KW_BEGIN Statements KW_END
void compileGroupSt(void) {
  assert("Parsing a group statement ....");
  // TODO
  eat(KW_BEGIN);
  compileStatements();
  eat(KW_END);
  assert("Group statement parsed ....");
}

// 60) IfSt ::= KW_IF Condition KW_THEN Statement ElseSt
void compileIfSt(void) {
  assert("Parsing an if statement ....");
  eat(KW_IF);
  compileCondition();
  eat(KW_THEN);
  compileStatement();
  if (lookAhead->tokenType == KW_ELSE){
    compileElseSt();
  }
  assert("If statement parsed ....");
}

// ??????????
// 61) ElseSt::= KW_ELSE statement
// 62) ElseSt::= 
void compileElseSt(void) {
  eat(KW_ELSE);
  compileStatement();
}


// 63) WhileSt::= KW_WHILE Condition KW_DO Statement
void compileWhileSt(void) {
  assert("Parsing a while statement ....");
  // TODO
  eat(KW_WHILE);
  compileCondition();
  eat(KW_DO);
  compileStatement();
  assert("While statement parsed ....");
}

// 64) ForSt::= KW_FOR VariableIdent SB_ASSIGN Expression KW_TO Expression KW_DO Statement
void compileForSt(void) {
  assert("Parsing a for statement ....");
  // TODO
  eat(KW_FOR);
  eat(TK_IDENT);
  eat(SB_ASSIGN);
  compileExpression();
  eat(KW_TO);
  compileExpression();
  eat(KW_DO);
  compileStatement();
  assert("For statement parsed ....");
}

// ?????
// 65) Arguments ::= SB_LPAR Expression Arguments2 SB_RLAR
// 66) Arguments ::= 
void compileArguments(void) {
  // TODO
  switch (lookAhead->tokenType) {
  case SB_LPAR:
      eat(SB_LPAR);
      compileExpression();
      compileArguments2();
      eat(SB_RPAR);
      break;
  // Follow - same as call statement as statement:
  case SB_SEMICOLON:
  case KW_END:
  case KW_ELSE:
  // Follow - term2
  case SB_TIMES:
  case SB_SLASH:
  // Follow - expression3
  // Follow (For statement)
  case KW_TO:
  case KW_DO:
  // Follow (arguments2)
  case SB_COMMA:
  // Follow (condition2)
  case SB_EQ:
  case SB_NEQ:
  case SB_LE:
  case SB_LT:
  case SB_GE:
  case SB_GT:
  // Follow (factor)
  case SB_RPAR:
  // Follow (indexes)
  case SB_RSEL:
  // Follow (if statement)
  case KW_THEN:
      break;
  // Error
  default:
      error(ERR_INVALIDARGUMENTS, lookAhead->lineNo, lookAhead->colNo);
      break;
  }
}


// 67) Arguments2::= SB_COMMA Expression Arguments2
// 68) Arguments2::= 
void compileArguments2(void) {
  // TODO
  switch (lookAhead->tokenType) {
  case SB_COMMA:
      eat(SB_COMMA);
      compileExpression();
      compileArguments2();
      break;
  // Follow
  case SB_RPAR:
      break;
  // Error:
  default:
      error(ERR_INVALIDARGUMENTS, lookAhead->lineNo, lookAhead->colNo);
      break;
  }
}


// 68) Condition ::= Expression Condition2
void compileCondition(void) {
  // TODO
  compileExpression();
  compileCondition2();
}


// 69) Condition2::= SB_EQ Expression
// 70) Condition2::= SB_NEQ Expression
// 71) Condition2::= SB_LE Expression
// 72) Condition2::= SB_LT Expression
// 73) Condition2::= SB_GE Expression
// 74) Condition2::= SB_GT Expression
void compileCondition2(void) {
  // TODO
  switch(lookAhead->tokenType){
    case SB_EQ:
      eat(SB_EQ);
      compileExpression();
      break;
    case SB_NEQ:
      eat(SB_NEQ);
      compileExpression();
      break;
    case SB_LE:
      eat(SB_LE);
      compileExpression();
      break;
    case SB_LT:
      eat(SB_LT);
      compileExpression();
      break;
    case SB_GE:
      eat(SB_GE);
      compileExpression();
      break;
    case SB_GT:
      eat(SB_GT);
      compileExpression();
      break;
    default:
      error(ERR_INVALIDARGUMENTS, lookAhead->lineNo, lookAhead->colNo);
      break;
  }
}

// 75) Expression ::= SB_PLUS Expression2
// 76) Expression ::= SB_MINUS Expression2
// 77) Expression ::= Expression2
void compileExpression(void) {
  assert("Parsing an expression");
  // TODO
  switch(lookAhead->tokenType){
    case SB_PLUS:
      eat(SB_PLUS);
      compileExpression2();
      break;
    case SB_MINUS:
      eat(SB_MINUS);
      compileExpression2();
      break;
    default:
      compileExpression2();
      break;
  }
  assert("Expression parsed");
}

// 78) Expression2 ::= Term Expression3
void compileExpression2(void) {
  // TODO
  compileTerm();
  compileExpression3();
}


// 79) Expression3 ::= SB_PLUS Term Expression3
// 80) Expression3 ::= SB_MINUS Term Expression3
// 81) Expression3 ::= 
void compileExpression3(void) {
  // TODO
  switch(lookAhead->tokenType) {
  case SB_PLUS:
      eat(SB_PLUS);
      compileTerm();
      compileExpression3();
      break;
  case SB_MINUS:
      eat(SB_MINUS);
      compileTerm();
      compileExpression3();
      break;
  // Follow (statement)
  case SB_SEMICOLON:
  case KW_END:
  case KW_ELSE:
  // Follow (For statement)
  case KW_TO:
  case KW_DO:
  // Follow (arguments2)
  case SB_COMMA:
  // Follow (condition2)
  case SB_EQ:
  case SB_NEQ:
  case SB_LE:
  case SB_LT:
  case SB_GE:
  case SB_GT:
  // Follow (factor)
  case SB_RPAR:
  // Follow (indexes)
  case SB_RSEL:
  // Follow (if statement)
  case KW_THEN:
      break;
  // Error
  default:
      error(ERR_INVALIDEXPRESSION, lookAhead->lineNo, lookAhead->colNo);
      break;
  }
}

// 82) Term ::= Factor Term2
void compileTerm(void) {
  // TODO
  compileFactor();
  compileTerm2();
}

// 83) Term2 ::= SB_TIMES Factor Term2
// 84) Term2 ::= SB_SLASH Factor Term2
// 85) Term2 ::= 
void compileTerm2(void) {
  // TODO
  switch (lookAhead->tokenType) {
  case SB_TIMES:
      eat(SB_TIMES);
      compileFactor();
      compileTerm2();
      break;
  case SB_SLASH:
      eat(SB_SLASH);
      compileFactor();
      compileTerm2();
      break;
  // Follow - same as expression3
  case SB_PLUS:
  case SB_MINUS:
  // Follow (statement)
  case SB_SEMICOLON:
  case KW_END:
  case KW_ELSE:
  // Follow (For statement)
  case KW_TO:
  case KW_DO:
  // Follow (arguments2)
  case SB_COMMA:
  // Follow (condition2)
  case SB_EQ:
  case SB_NEQ:
  case SB_LE:
  case SB_LT:
  case SB_GE:
  case SB_GT:
  // Follow (factor)
  case SB_RPAR:
  // Follow (indexes)
  case SB_RSEL:
  // Follow (if statement)
  case KW_THEN:
      break;
  default:
      error(ERR_INVALIDTERM, lookAhead->lineNo, lookAhead->colNo);
      break;
  }
}

// 86) Factor ::= UnsignedConstant
// 87) Factor ::= Variable
// 88) Factor ::= FunctionApptication
// 89) Factor ::= SB_LPAR Expression SB_RPAR
void compileFactor(void) {
  // TODO
  switch (lookAhead->tokenType) {
  case TK_NUMBER:
  case TK_CHAR:
      compileUnsignedConstant();
      break;
  case SB_LPAR:
      eat(SB_LPAR);
      compileExpression();
      eat(SB_RPAR);
      break;
  case TK_IDENT:
      eat(TK_IDENT);
      switch(lookAhead->tokenType) {
      case SB_LSEL:
          compileIndexes();
          break;
      case SB_LPAR:
          compileArguments();
          break;
      default:
          break;
      }
      break;
  default:
      error(ERR_INVALIDFACTOR, lookAhead->lineNo, lookAhead->colNo);
      break;
  }
}

// 92) Indexes ::= SB_LSEL Expression SB_RSEL Indexes
// 93) Indexes ::= 
void compileIndexes(void) {
  // TODO
  if (lookAhead->tokenType == SB_LSEL) {
      eat(SB_LSEL);
      compileExpression();
      eat(SB_RSEL);
      compileIndexes();
  }
}

int compile(char *fileName) {
  if (openInputStream(fileName) == IO_ERROR)
    return IO_ERROR;

  currentToken = NULL;
  lookAhead = getValidToken();

  compileProgram();

  free(currentToken);
  free(lookAhead);
  closeInputStream();
  return IO_SUCCESS;

}
