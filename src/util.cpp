#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "util.h"


//************************************
// Method:    getInput
// Returns:   void
// Parameter: char * str ������ַ���
// Parameter: unsigned int size �������󳤶�
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
// Description: ����㷨
// @param: max ���ֵ
// @param: min ��Сֵ
// @return: �����
//
int randomEx( int min,int max )
{
    static int count = 10000;
    count ++;
    srand( (unsigned)time( NULL ) % count);
    return rand()%max + min;
}


//
// �ж�һ���ַ����Ƿ�Ϊ����
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
// ���ַ���ת��Ϊ���֣����ת��ʧ�ܣ�����INT_MAX, ��0x7fffffff
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
// * Description: ��һ���ַ���ȫ��תΪСд
// * @param: str ԭ�ַ���
// * @param: result ת������ַ���
// * @param: size ������ַ�������
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
// * ��ָ���ָ����ָ�һ���ַ������ַ��������С�
// * delim: �ָ���
// * input:  ���ָ��ַ�������ӿ���̨��ȡ��һ���ַ�
// * buffer: ����ָ�������ַ������顣
// * size: buffer�Ĵ�С��������ĵ��ʸ���
// * return: ���ص��ʵĸ������Ƿ�ʱ����0
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
