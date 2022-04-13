/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#ifndef __READER_H__
#define __READER_H__

#define IO_ERROR 0
#define IO_SUCCESS 1

// doc ki tu tu strea vao
int readChar(void);
// mo stream de doc dau vao tu file
int openInputStream(char *fileName);
// dong kenh vao
void closeInputStream(void);

#endif
