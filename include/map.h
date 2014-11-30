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
    char type;     //地形，如'0'空地,'1'茅屋，'T'道具屋
    Player *owner; //土地主人，公共资产owner为null
    int price;     //土地初始地价；对于矿地，代表的是点数
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
