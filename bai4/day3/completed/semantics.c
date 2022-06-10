/*
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdlib.h>
#include <string.h>
#include "semantics.h"
#include "error.h"

extern SymTab *symtab;
extern Token *currentToken;

// Trả về thông tin của 1 Object
// Tìm trong tất cả Scope của chương trình
Object *lookupObject(char *name)
{
  // TODO
  Object *object = NULL;
  Scope *currentScope = symtab->currentScope;

  while (currentScope != NULL)
  {
    // Tìm Object trong list các Objects của Scope hiện tại
    object = findObject(currentScope->objList, name);
    if (object != NULL)
    {
      return object;
    }
    // Nếu không tìm thấy -> Tìm Object ở Scope bên ngoài
    currentScope = currentScope->outer;
  }

  // Tìm Object ở Scope Global (Scope ngoài cùng, ngoài PROGRAM)
  object = findObject(symtab->globalObjectList, name);
  if (object != NULL)
    return object;

  return NULL;
}
// Kiểm tra xem IDENT này đã được định nghĩa TRONG SCOPE HIỆN TẠI chưa?
// Dùng khi khai báo
void checkFreshIdent(char *name)
{
  // TODO
  // Nếu tìm thấy IDENT đã được định nghĩa -> Báo lỗi
  if (findObject(symtab->currentScope->objList, name) != NULL)
  {
    error(ERR_DUPLICATE_IDENT, currentToken->lineNo, currentToken->colNo);
  }
}

// Check xem IDENT đã được khai báo chưa (tìm trong cả Scope ngoài)
// Nếu đã khai báo -> Trả về Object có tên là IDENT đấy
// Nếu chưa khai báo -> Trả về lỗi
// Dùng khi gán
Object *checkDeclaredIdent(char *name)
{
  // TODO
  Object *object = lookupObject(name);

  if (object == NULL)
  {
    error(ERR_UNDECLARED_IDENT, currentToken->lineNo, currentToken->colNo);
  }
  return object;
}

// Check xem CONSTANT đã được khai báo chưa (tìm trong cả Scope ngoài)
// Nếu đã khai báo -> Trả về Object có tên là tên của CONSTANT đấy
// Nếu chưa khai báo -> Trả về lỗi
// Dùng khi gán
Object *checkDeclaredConstant(char *name)
{
  // TODO
  Object *obj = lookupObject(name);
  if (obj == NULL)
  {
    error(ERR_UNDECLARED_CONSTANT, currentToken->lineNo, currentToken->colNo);
  }
  if (obj->kind != OBJ_CONSTANT)
    error(ERR_INVALID_CONSTANT, currentToken->lineNo, currentToken->colNo);

  return obj;
}

// Check xem TYPE đã được khai báo chưa (tìm trong cả Scope ngoài)
// Nếu đã khai báo -> Trả về Object có tên là tên của TYPE đấy
// Nếu chưa khai báo -> Trả về lỗi
// Dùng khi gán
Object *checkDeclaredType(char *name)
{
  // TODO
  Object *obj = lookupObject(name);
  if (obj == NULL)
    error(ERR_UNDECLARED_TYPE, currentToken->lineNo, currentToken->colNo);
  if (obj->kind != OBJ_TYPE)
    error(ERR_INVALID_TYPE, currentToken->lineNo, currentToken->colNo);
  
  return obj;
}

// Check xem VAR đã được khai báo chưa (tìm trong cả Scope ngoài)
// Nếu đã khai báo -> Trả về Object có tên là tên của VAR đấy
// Nếu chưa khai báo -> Trả về lỗi
// Dùng khi gán
Object *checkDeclaredVariable(char *name)
{
  // TODO
  Object *obj = lookupObject(name);
  if (obj == NULL)
    error(ERR_UNDECLARED_VARIABLE, currentToken->lineNo, currentToken->colNo);
  if (obj->kind != OBJ_VARIABLE) 
    error(ERR_INVALID_VARIABLE, currentToken->lineNo, currentToken->colNo);
  
  return obj;
}

// Check xem FUNCTION đã được khai báo chưa (tìm trong cả Scope ngoài)
// Nếu đã khai báo -> Trả về Object có tên là tên của FUNCTION đấy
// Nếu chưa khai báo -> Trả về lỗi
// Dùng khi gán
Object *checkDeclaredFunction(char *name)
{
  // TODO
  Object *obj = lookupObject(name);
  if (obj == NULL)
    error(ERR_UNDECLARED_FUNCTION, currentToken->lineNo, currentToken->colNo);
  // Nếu tìm đc Object nhưng kiểu ko p FUNCTION -> báo lỗi
  if (obj->kind != OBJ_FUNCTION)
    error(ERR_INVALID_FUNCTION, currentToken->lineNo, currentToken->colNo);

  return obj;
}

// Check xem PROCEDURE đã được khai báo chưa (tìm trong cả Scope ngoài)
// Nếu đã khai báo -> Trả về Object có tên là tên của PROCEDURE đấy
// Nếu chưa khai báo -> Trả về lỗi
// Dùng khi gán
Object *checkDeclaredProcedure(char *name)
{
  // TODO
  Object *obj = lookupObject(name);
  if (obj == NULL)
    error(ERR_UNDECLARED_PROCEDURE, currentToken->lineNo, currentToken->colNo);
  // Nếu tìm đc Object nhưng kiểu ko p PROCEDURE -> báo lỗi
  if (obj->kind != OBJ_PROCEDURE)
    error(ERR_INVALID_PROCEDURE, currentToken->lineNo, currentToken->colNo);

  return obj;
}

Object *checkDeclaredLValueIdent(char *name)
{
  // TODO
  Object *obj = lookupObject(name);
  if (obj == NULL)
    error(ERR_UNDECLARED_IDENT, currentToken->lineNo, currentToken->colNo);
  switch (obj->kind) {
    case OBJ_VARIABLE:
    case OBJ_PARAMETER:
      break;
    case OBJ_FUNCTION:
      if (obj != symtab->currentScope->owner)
        error(ERR_INVALID_IDENT, currentToken->lineNo, currentToken->colNo);
      break;
    default:
      error(ERR_INVALID_IDENT, currentToken->lineNo, currentToken->colNo);
  }
  return obj;
}
