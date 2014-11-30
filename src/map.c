#include "map.h"
#include "player.h"
#include "rich.h"

#include "util.h"
#include <string.h>

#define MAX_LAND_LEVEL '3'


static char g_chrMap[HEIGHT][WIDTH] = {
    "S0000000000000H0000000000000T",
    "$                           0",
    "$                           0",
    "$                           0",
    "$                           0",
    "$                           0",
    "$                           0",
    "M0000000000000P0000000000000G"
};

//地图上每块地对应的价格基数
static char g_mapPrice[HEIGHT][WIDTH] = {
    "22222222222222222222222222222",
    "3                           5",
    "4                           5",
    "2                           5",
    "5                           5",
    "4                           5",
    "1                           5",
    "33333333333333333333333333333"
};

char getMapChr(int row, int column)
{
    return g_chrMap[row][column];
}

void setMapChr(int row,int column,char chr)
{
    g_chrMap[row][column] = chr;
}

PLACE_TYPE getPlaceType(Place *place,Player *player)
{
    if (place->owner == player)
    {
        return OWN_LAND;
    }
    else if (place->owner != NULL && place->owner != player)
    {
        return OTHERS_LAND;
    }
    return (PLACE_TYPE) place->type;
}

unsigned int getPlaceNum(Game *game)
{
    return game->placeNum;
}

Place* getPlaceByIndex(Game *game,unsigned int idx)
{
    return &(game->map[idx]);
}

/************************************************************************/
/* 获取每块地的初始价格或者点数                                         */
/************************************************************************/
static int getPlaceInitPrice(char type, unsigned int x, unsigned int y)
{
    int base=-1;

    switch(type)
    {
    case LAND:
        base = 100;
        break;
    case MINE:
        base = 20;
        break;
    default:
        break;
    }
    return base*(g_mapPrice[y][x]-'0');
}

static char *getMapArray()
{
    return &g_chrMap[0][0];
}

static void addPlace(Game *game, Place *place )
{
    game->map[game->placeNum] = *place;
    game->placeNum++;
}


/************************************************************************/
/* 判断两块地是否相邻                                                   */
/************************************************************************/
static int isConjointPlace(Place *first, Place *second)
{
    if ((first->x == second->x) && 1 == abs(((int)first->y - (int)second->y)))
    {
        return TRUE;
    }
    else if ((first->y == second->y) && 1 == abs(((int)first->x - (int)second->x)))
    {
        return TRUE;
    }

    return FALSE;
}

static int isInvalidPlace( char  mapChr) 
{
    return ('\0' == mapChr) || (' ' == mapChr);
}

static void initializePlace( Place *place, char * mapChars, unsigned int placeIndex ) 
{
    memset(place,0,sizeof(Place));
    place->type = mapChars[placeIndex];
    place->owner = NULL;
    place->x = placeIndex%WIDTH;
    place->y = placeIndex/WIDTH;
    place->price = getPlaceInitPrice(place->type,place->x, place->y);
}

static int isFirstPlaceToAdd( Game * game ) 
{
    return (getPlaceNum(game)==0);
}

static Place* lastPlaceAdded( Game * game ) 
{
    return getPlaceByIndex(game,getPlaceNum(game)-1);
}

/************************************************************************/
/* 加载地图的算法                                                       */
/************************************************************************/
void initMap(Game *game)
{
    char *mapChars;
    Place place;
    unsigned int i;
    int invalidPlaceCount;
    int length;
    
    length = WIDTH*HEIGHT;
    mapChars = getMapArray();
    while(length >0)
    {
        invalidPlaceCount = 0;  
        for(i = 0; i<WIDTH*HEIGHT; i++)
        {
            if (isInvalidPlace(mapChars[i]))
            {
                invalidPlaceCount++;
                continue;
            }
            initializePlace(&place, mapChars, i);            
            if (isFirstPlaceToAdd(game) || (isConjointPlace(lastPlaceAdded(game), &place)))
            {
                addPlace(game,&place);
                mapChars[i]=' ';
            }
        }
        length = WIDTH*HEIGHT - invalidPlaceCount;
    }
}

int isHighestLevel( Place *place )
{
    return place->type == MAX_LAND_LEVEL;
}
