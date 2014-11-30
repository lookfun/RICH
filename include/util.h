#ifndef UTIL_H
#define UTIL_H

#ifdef RICH_COMPILE_GCC
#include <stdarg.h>
#include <stddef.h>
typedef unsigned short      WORD;

#define INT_MIN     (-2147483647 - 1) /* minimum (signed) int value */
#define INT_MAX       2147483647    /* maximum (signed) int value */

#define FOREGROUND_BLUE      0x0001 // text color contains blue.
#define FOREGROUND_GREEN     0x0002 // text color contains green.
#define FOREGROUND_RED       0x0004 // text color contains red.
#define FOREGROUND_INTENSITY 0x0008 // text color is intensified.

#ifndef TRUE
#define TRUE                1
#endif

#ifndef FALSE
#define FALSE               0
#endif

#else
#include <Windows.h>
#endif
#include <stdlib.h>
#include <string.h>


#ifdef __cplusplus
extern "C"
{
#endif

#define MAX_INPUT_SIZE 128
#define MAX_TOKEN_SIZE 64 //每个单词的最大长度


#define  COLOR_RED FOREGROUND_RED
#define  COLOR_GREEN FOREGROUND_GREEN
#define  COLOR_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)
#define  COLOR_BLUE FOREGROUND_BLUE
#define  COLOR_DEFAULT (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

void getInput(char *str,unsigned int);
int isDigit(char *str);
int str2int(char *str);
int split(const char* delim,char* input,char buffer[][MAX_TOKEN_SIZE] ,unsigned int size);
void toLower(char *str, char* result,unsigned int size);

//int randomEx(int min,int max ); //function name conflict with system API
int randomEx(int min,int max );

void ColoredPrintChr(WORD color, char chr);
void ColoredPrintf(WORD color, const char* fmt, ...);

void printMsg(char *);
void printChr(char);




#ifdef __cplusplus
}
#endif

#endif

