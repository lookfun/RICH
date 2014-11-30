#ifndef PLAYER_H
#define PLAYER_H

#include "rich_decl.h"

#ifdef __cplusplus
extern "C"
{
#endif


struct Player{
    int id;     //玩家编号，1开始
    char *name; //玩家姓名
    int money;  //资金
    int points; //点数
    unsigned int pos;     //玩家当前位置
    char acronym;         //玩家显示在屏幕的符号
    unsigned short color; //玩家颜色
};



void initializePlayer(Game *game);
int getPlayerNum(Game *game);
Player* getCurrentPlayer(Game *game);

Player *getPlayerByIndex(Game *game,int idx);
unsigned int getPlayerPosition(Player *);

void goRandomSteps(Game *game);


#ifdef __cplusplus
}
#endif
#endif
