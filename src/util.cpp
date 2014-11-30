#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "util.h"


//************************************
// Method:    getInput
// Returns:   void
// Parameter: char * str 保存的字符串
// Parameter: unsigned int size 允许的最大长度
//************************************
void getInput(char *str, unsigned int size)
{
    if (fgets(str,size,stdin) == NULL)
    {
        return;
    }
        
    if (str[strlen(str)-1] == '\n') //delete '\n'
    {
        str[strlen(str)-1] = '\0'; 
    }
    else
    {
        fflush(stdin);
    }
}



// 
// Description: 随机算法
// @param: max 最大值
// @param: min 最小值
// @return: 随机数
//
int randomEx( int min,int max )
{
    static int count = 10000;
    count ++;
    srand( (unsigned)time( NULL ) % count);
    return rand()%max + min;
}


//
// 判断一个字符串是否为数字
//
int isDigit(char *str)
{
    while(*str)   
    {
        if ((*str) == '-')
        {
            str++;
            continue;
        }
        if(!isdigit(*str++))  
            return   0;  
    }  
    return   1;   
}

// 
// 将字符串转换为数字，如果转换失败，返回INT_MAX, 即0x7fffffff
// 
int str2int(char *str)
{
    int val;
    if (!isDigit(str)) 
    {
        return INT_MAX;
    }
    val = atoi(str);
    if (val == INT_MIN)
    {
        return INT_MAX;
    }
    return val;
}

#ifdef RICH_COMPILE_GCC
/*   string   to   low*/ 
inline   char*   strlwr(char* str) 
{ 
    char*   orig   =   str; 
    //   process   the   string 
	while(*orig != '\0')
	{
		*orig++ = tolower(*orig);
	}
	return str;
} 
#endif

// *
// * Description: 将一个字符串全部转为小写
// * @param: str 原字符串
// * @param: result 转换后的字符串
// * @param: size 保存的字符串长度
// * @return:
// *
void toLower(char *str,char* result,unsigned int size)
{
    char *buf = (char *) malloc(size);
    strncpy(buf,str,size);
    strncpy(result,strlwr(buf),size);
    free(buf);
}




// *
// * 以指定分隔符分割一个字符串到字符串数组中。
// * delim: 分隔符
// * input:  待分割字符串，如从控制台读取的一行字符
// * buffer: 保存分隔结果的字符串数组。
// * size: buffer的大小，即保存的单词个数
// * return: 返回单词的个数。非法时返回0
// *
int split(const char* delim,char* input,char buffer[][MAX_TOKEN_SIZE],unsigned int size)
{
    unsigned int count = 1;
    char tempstr[MAX_INPUT_SIZE];
    char *str=NULL;
    if (strlen(input) == 0 || strlen(input) >= MAX_INPUT_SIZE) 
    {
        return 0;
    }
    strncpy(tempstr,input,MAX_INPUT_SIZE-1);
    str = strtok(tempstr,delim);
    if (str == NULL) 
    {
        return 0;
    }
    strncpy(buffer[0],str,MAX_TOKEN_SIZE-1);    
    buffer[0][MAX_TOKEN_SIZE-1] = '\0';
    str = strtok(NULL,delim);
    while(str && (count < size))
    {
        strncpy(buffer[count],str,MAX_TOKEN_SIZE-1);
        buffer[count][MAX_TOKEN_SIZE-1] = '\0';
        count++;
        str = strtok(NULL,delim);     
    }
    return count;
}

void ColoredPrintf(WORD color, const char* fmt, ...) 
{
    va_list args;
    va_start(args, fmt);

#ifdef RICH_COMPILE_GCC
    vprintf(fmt, args);
#else
    const HANDLE stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    // Gets the current text color.
    CONSOLE_SCREEN_BUFFER_INFO buffer_info;
    GetConsoleScreenBufferInfo(stdout_handle, &buffer_info);
    const WORD old_color_attrs = buffer_info.wAttributes;

    SetConsoleTextAttribute(stdout_handle,color | FOREGROUND_INTENSITY);
    vprintf(fmt, args);

    // Restores the text color.
    SetConsoleTextAttribute(stdout_handle, old_color_attrs);
#endif
    //printf(fmt,args);	
    va_end(args);
}

void ColoredPrintChr(WORD color, char chr)
{
    ColoredPrintf(color, "%c", chr);
}

void printMsg(char *msg)
{
    printf("%s",msg);
}
void printChr(char chr)
{
    printf("%c",chr);
}
