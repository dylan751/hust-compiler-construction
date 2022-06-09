/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>

#include "symtab.h"
#include "debug.h"

extern SymTab* symtab;
/******************************************************************/

int main() {
  Object* obj;

  initSymTab();

  // Tạo Object Program
  obj = createProgramObject("PRG");
  enterBlock(obj->progAttrs->scope);

  // Tạo Const: CONST c1 = 10;
  obj = createConstantObject("c1");
  obj->constAttrs->value = makeIntConstant(10);
  declareObject(obj);

  // Tạo Const: CONST c2 = 'a';
  obj = createConstantObject("c2");
  obj->constAttrs->value = makeCharConstant('a');
  declareObject(obj);

  // Tạo Type: TYPE t1 = ARRAY(.10.) OF INTEGER;
  obj = createTypeObject("t1");
  obj->typeAttrs->actualType = makeArrayType(10,makeIntType());
  declareObject(obj);

  // Tạo Variable: VAR v1: Integer
  obj = createVariableObject("v1");
  obj->varAttrs->type = makeIntType();
  declareObject(obj);

  // Tạo Variable: VAR v2: ARRAY(.10.) OF ARRAY(.10.) OF INTEGER;
  obj = createVariableObject("v2");
  obj->varAttrs->type = makeArrayType(10,makeArrayType(10,makeIntType()));
  declareObject(obj);

  // Tạo Function: FUNCTION f(p1: Integer; p2: Char): Integer;
  obj = createFunctionObject("f");
  obj->funcAttrs->returnType = makeIntType(); // Kiểu trả về
  declareObject(obj);
  
    enterBlock(obj->funcAttrs->scope);
 
    // Tạo param1: p1: Integer;
    obj = createParameterObject("p1", PARAM_VALUE, symtab->currentScope->owner);
    obj->paramAttrs->type = makeIntType();
    declareObject(obj);

    // Tạo param1: p1: Char;
    obj = createParameterObject("p2", PARAM_REFERENCE, symtab->currentScope->owner);
    obj->paramAttrs->type = makeCharType();
    declareObject(obj);

    exitBlock();

  // Tạo Procedure: PROCEDURE(v1: Integer);
  obj = createProcedureObject("p");
  declareObject(obj);
  
    // Vào trong Scope của Procedure
    enterBlock(obj->procAttrs->scope);
 
    // Tạo param1: v1: Integer;
    obj = createParameterObject("v1", PARAM_VALUE, symtab->currentScope->owner);
    obj->paramAttrs->type = makeIntType();
    declareObject(obj);

    // CONST c1 = 'a';
    obj = createConstantObject("c1");
    obj->constAttrs->value = makeCharConstant('a');
    declareObject(obj);
    
    // CONST c3 = 10;
    obj = createConstantObject("c3");
    obj->constAttrs->value = makeIntConstant(10);
    declareObject(obj);

    // TYPE t1 = Integer;
    obj = createTypeObject("t1");
    obj->typeAttrs->actualType = makeIntType();
    declareObject(obj);

    // TYPE t2 = ARRAY(.10.) OF INTEGER;
    obj = createTypeObject("t2");
    obj->typeAttrs->actualType = makeArrayType(10,makeIntType());
    declareObject(obj);

    // VAR v2: ARRAY(.10.) OF INTEGER;
    obj = createVariableObject("v2");
    obj->varAttrs->type = makeArrayType(10,makeIntType());
    declareObject(obj);

    // VAR v3: Char;
    obj = createVariableObject("v3");
    obj->varAttrs->type = makeCharType();
    declareObject(obj);

    // Thoát tra Scope bên ngoài của Procedure
    exitBlock();


  // Thoát tra Scope bên ngoài của Program
  exitBlock();
  printObject(symtab->program,0); // In ra các Object trong PROGRAM trong chương trình
  cleanSymTab();
    
  return 0;
}
