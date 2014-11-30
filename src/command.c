#include "command.h"
#include "player.h"
#include "rich.h"
#include "util.h"
#include <stdio.h>
#ifdef RICH_COMPILE_GCC
#include <string.h>
#endif

#define MAX_TOKEN 2

#define HELP "help"
#define QUIT "quit"
#define ROLL "roll"

#ifdef __cplusplus
extern "C"
{
#endif

void Roll(Game *game,char *params);
void Help(Game *game,char *params);
void PrintGameInfo(Game *game,char *params);

#ifdef __cplusplus
}
#endif

typedef void (*CMD_PROC)(Game *game,char *params);

typedef struct CMD_DESC
{
    char name[MAX_INPUT_SIZE];
    CMD_PROC pCmdProc;
}CMD_DESC;

/*����ע���*/
CMD_DESC cmdList[]=
{
    {ROLL, Roll},
    {HELP, Help},

    {"print",PrintGameInfo} //�����Զ������Ե�У��
};

CMD_PROC cmdParse(char *cmd)
{
    unsigned int  i;
    for (i = 0; i < sizeof(cmdList)/sizeof(CMD_DESC); i++)
    {
        if(0 == strcmp(cmd, cmdList[i].name))
        {
            return cmdList[i].pCmdProc;
        }
    }

    return NULL;
}

void getCmdName(char *inputCmd,char *cmdName,int size)
{
    int tokenNum = 0;
    char cmdTokens[MAX_TOKEN][MAX_TOKEN_SIZE];
    tokenNum = split(" ",inputCmd,cmdTokens,MAX_TOKEN);
    if (tokenNum == 0)
    {
        strcpy(cmdName,"");
        return;
    }
    strncpy(cmdName,cmdTokens[0],size-1);
}
char* getParams(char *inputCmd)
{
    char *p = strstr(inputCmd," ");
    if (!p)
    {
        return NULL;
    }
    while( *p == ' ')
    {
        p++;
    }
    if (*p == '\0')
    {
        return NULL;
    }
    return p;
}

static void printCurrentPlayer( Game * game ) 
{
    Player *player = getCurrentPlayer(game);
    ColoredPrintf(player->color,"%s>",player->name);
}

static void getLowerCmd( char* lowercaseCmd ) 
{
    char inputcmd[MAX_INPUT_SIZE];
    memset(inputcmd,0,sizeof(inputcmd));
    getInput(inputcmd,MAX_INPUT_SIZE);
    toLower(inputcmd,lowercaseCmd,MAX_INPUT_SIZE);
}

static void runCmd( char * cmd, Game * game ) 
{
    char cmdName[MAX_TOKEN_SIZE];
    CMD_PROC pFunc;
    memset(cmdName,0,sizeof(cmdName));
    getCmdName(cmd,cmdName,MAX_TOKEN_SIZE);
    pFunc = cmdParse(cmdName);

    if (pFunc != NULL)
    {
        pFunc(game,getParams(cmd));
    }
    else
    {
        printMsg("Error Command.\n");
    }
}

void run(Game *game)
{
    char lowercaseCmd[MAX_INPUT_SIZE];
    memset(lowercaseCmd,0,sizeof(lowercaseCmd));

    for(;;)
    {       
        printCurrentPlayer(game);		
        getLowerCmd(lowercaseCmd);
        if (strcmp(lowercaseCmd,QUIT) == 0)
        {
            printMsg("Game Over!!!\n");
            break;
        }
        runCmd(lowercaseCmd, game);
    }

}


void Roll(Game *game,char *params)
{
    goRandomSteps(game);
}

void Help(Game *game,char *params)
{
    char help_string[] ="\
***********************************��ͼ����***********************************\n\
0:�յ�; $:���; S:���0; H:ҽԺ14; T:������28; G:��Ʒ��35; P:����49; M:ħ����63��\n\n\
***********************************�������***********************************\n\
roll:       ���������\n\
block n:    ʹ��·�ϡ�nΪ�����ҵ�ǰλ�õľ��룬-10~10��Χ����Ч��\n\
bomb n:     ʹ��ը����nΪ�����ҵ�ǰλ�õľ��룬-10~10��Χ����Ч��\n\
robot :     ʹ�û������ޡ�����ɨǰ��·����10�����ڵ��������ߣ���ը����·�ϡ�\n\
query:      ��ѯ��ǰ����ʲ���Ϣ��\n\
help:       ������\n\
quit:       �˳���Ϸ��\n" ;

    printMsg(help_string);
}

void PrintGameInfo(Game *game,char *params)
{
    int i;
    static int num =1;
    Player *player;
    for (i=0;i<game->playerNum;i++)
    {
        player=getPlayerByIndex(game,i);
        printf("%d.%c: %d %d\n",num,player->acronym,player->money,player->points);
    }
    num++;
}
