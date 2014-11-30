#ifndef PLAYER_H
#define PLAYER_H

#include "rich_decl.h"

#ifdef __cplusplus
extern "C"
{
#endif


struct Player{
    int id;     //��ұ�ţ�1��ʼ
    char *name; //�������
    int money;  //�ʽ�
    int points; //����
    unsigned int pos;     //��ҵ�ǰλ��
    char acronym;         //�����ʾ����Ļ�ķ���
    unsigned short color; //�����ɫ
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
