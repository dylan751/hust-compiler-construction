/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#ifndef __CHARCODE_H__
#define __CHARCODE_H__

typedef enum {
  CHAR_SPACE,           // khoang trong
  CHAR_LETTER,          // chu cai
  CHAR_DIGIT,           // chu so
  CHAR_PLUS,            // '+'
  CHAR_MINUS,           // '-'
  CHAR_TIMES,           // '*'
  CHAR_SLASH,           // '/'
  CHAR_LT,              // '<'
  CHAR_GT,              // '>'
  CHAR_EXCLAIMATION,    // '!'
  CHAR_EQ,              // '='
  CHAR_COMMA,           // ','
  CHAR_PERIOD,          // '.'
  CHAR_COLON,           // ':'
  CHAR_SEMICOLON,       // ';'
  CHAR_SINGLEQUOTE,     // '\''
  CHAR_LPAR,            // '('
  CHAR_RPAR,            // ')'
  CHAR_UNKNOWN          // cac ki tu con lai
} CharCode;

#endif
