#ifndef RICH_H
#define RICH_H
#include "player.h"
#include "map.h"

#ifdef __cplusplus
extern "C"
{
#endif
#define  DEFAULT_MONEY 10000
#define  MIN_INIT_MONEY 1000
#define  MAX_INIT_MONEY 50000

#define MAX_PLACE_NUM 512
#define MAX_PLAYER_NUM 4
#define MIN_PLAYER_NUM 2

struct Game{
    int init_money; //ÿλ��ҳ�ʼ�ʽ�

    int playerNum;  //��Ҹ���
    Player players[MAX_PLAYER_NUM];
    int currentPlayerIndex;

    unsigned int placeNum; //��ͼ���ȣ�����Ч�ؿ����
    Place map[MAX_PLACE_NUM];
};

Game * createGame();
void destroyGame(Game *game);
void initializeMoney(Game *game);



#ifdef __cplusplus
}
#endif
#endif
