#include "map.h"
#include "printMap.h"
#include "player.h"
#include "util.h"

static void printMapChars( unsigned short map_color[HEIGHT][WIDTH]) 
{
    unsigned int i,j;
    for(i=0;i<HEIGHT;i++)
    {
        for(j=0;j<WIDTH;j++)
        {
            if (0 != map_color[i][j])
            {
                ColoredPrintChr(map_color[i][j],getMapChr(i,j));
            }
            else
            {
                printChr(getMapChr(i,j));
            }
        }
        printMsg("\n");
    }
}

static void setTypeAndColorForEveryPlace(Game * game,unsigned short map_color[HEIGHT][WIDTH]) 
{
    unsigned int i;
    Place *place;
    for (i=0;i<getPlaceNum(game);i++)
    {
        place = getPlaceByIndex(game,i);
        setMapChr(place->y,place->x,place->type);
        if (place->owner != NULL)
        {
            map_color[place->y][place->x] = place->owner->color;
        }
    }
}

static void setPrintInfoForPlayers(Game * game,unsigned short map_color[HEIGHT][WIDTH]) 
{
    int i;
    Place *place;
    Player *player;
    for (i=0;i<getPlayerNum(game);i++)
    {
        player = getPlayerByIndex(game,i);
        place=getPlaceByIndex(game,getPlayerPosition(player));
        setMapChr(place->y,place->x,player->acronym);
        map_color[place->y][place->x] = player->color;
    }
}

void printMap(Game *game)
{
    unsigned short map_color[HEIGHT][WIDTH]; //记录地图上每个地块的显示颜色
    memset(map_color, 0, sizeof(map_color));

    //设置每个地块的字符和颜色
    setTypeAndColorForEveryPlace(game, map_color);

    //设置玩家的字符和颜色
    setPrintInfoForPlayers(game, map_color);

    //打印地图
    printMapChars(map_color);
}


