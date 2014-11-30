#ifndef MAP_H
#define MAP_H

#include "rich_decl.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum{
    START = 'S',
    LAND = '0',
    HOSPITAL = 'H',
    TOOLS_HOUSE = 'T',
    GIFT_HOUSE = 'G',
    PRISION = 'P',
    MINE = '$',
    MAGIC_HOUSE = 'M',
    OWN_LAND = 1,
    OTHERS_LAND = 2
}PLACE_TYPE;

#define WIDTH 30
#define HEIGHT 8

struct Place
{
    char type;     //���Σ���'0'�յ�,'1'é�ݣ�'T'������
    Player *owner; //�������ˣ������ʲ�ownerΪnull
    int price;     //���س�ʼ�ؼۣ����ڿ�أ�������ǵ���
    unsigned int x;
    unsigned int y;
};

void initMap(Game *game);
unsigned int getPlaceNum(Game *game);
Place* getPlaceByIndex(Game *game,unsigned int idx);
int isHighestLevel( Place *place );
char getMapChr(int row, int column);
void setMapChr(int row,int column,char chr);
PLACE_TYPE getPlaceType(Place *place,Player *player);
#define CHAR2INT(chr) (int)(chr-'0')
#define INT2CHAR(chr) (char)(chr+'0')

#ifdef __cplusplus
}
#endif
#endif
