#include "player.h"
#include "rich.h"
#include "map.h"
#include "printMap.h"
#include "util.h"
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif


static void buyLand(Place *place, Player *player);
static void upgradeLand(Place *,Player*);


#define MIN_DICE_VALUE 1
#define MAX_DICE_VALUE 6

typedef struct PlayerDisplay{
    char *name;
    char acronym;
    unsigned short color;
}PlayerDisplay;

PlayerDisplay g_playerDisplay[] = {
    {"钱夫人",'Q',COLOR_RED},
    {"阿土伯",'A',COLOR_GREEN},
    {"孙小美",'S',COLOR_YELLOW},
    {"金贝贝",'J',COLOR_BLUE}
};

int getPlayerNum(Game *game)
{
    return game->playerNum;
}

Player* getPlayerByIndex(Game *game,int idx)
{
    return &(game->players[idx]);
}

unsigned int getPlayerPosition(Player *player)
{
    return player->pos;
}

static int isSamePlayer(char *input)
{
    char copystr[MAX_INPUT_SIZE];
    unsigned int i,j;
    strncpy(copystr,input,strlen(input));
    for(i=0;i<strlen(input);i++)
    {
        for(j=i+1;j<strlen(input);j++)
        {
            if (copystr[i] == input[j])
            {
                return TRUE;
            }
        }
    }
    return FALSE;
}

static int notExistPlayer(char *input)
{
    unsigned int i;
    for (i=0;i<strlen(input);i++)
    {
        if (input[i] > '4' || input[i] < '1')
        {
            return TRUE;
        }
    }
    return FALSE;
}
static int getInputPlayer(char *input) 
{
    int playernum;
    do 
    {
        printMsg("请选择2~4位不重复玩家，输入编号即可。(1.钱夫人; 2.阿土伯; 3.孙小美; 4.金贝贝):\n");
        getInput(input,MAX_INPUT_SIZE);
        playernum = strlen(input);

    } while (playernum<MIN_PLAYER_NUM || playernum >MAX_PLAYER_NUM || isSamePlayer(input) || notExistPlayer(input));
    return playernum;
}

static void setPlayerProperties( Game * game, int index, int playerId ) 
{
    Player *player = &(game->players[index]);
    player->id = playerId;
    player->name = g_playerDisplay[playerId-1].name;
    player->color = g_playerDisplay[playerId-1].color;
    player->acronym = g_playerDisplay[playerId-1].acronym;
    player->money = game->init_money;
}

void initializePlayer(Game *game)
{
    char input[MAX_INPUT_SIZE];
    int i;

    game->playerNum = getInputPlayer(input);
    for (i=0;i<game->playerNum;i++)
    {
        setPlayerProperties(game, i, CHAR2INT(input[i]));
    }
}

void nextPlayer(Game *game)
{
    game->currentPlayerIndex = (game->currentPlayerIndex+1) % getPlayerNum(game);
}

Player *getCurrentPlayer(Game *game)
{
    return &(game->players[game->currentPlayerIndex]);
}

void updatePlayerPos(Player *player,int steps,unsigned int map_length)
{
    player->pos = (player->pos + steps) % map_length;
}

static void addPoints( Player * player, int points) 
{
    player->points += points;
    printf("获得点数%d，剩余点数%d\n",points,player->points );
}

void arriveAtDifferentPlace( Place * curr_place, Player * player ) 
{
    PLACE_TYPE type = getPlaceType(curr_place,player);

    switch (type)
    {
    case LAND:
        buyLand(curr_place,player);
    	 break;
    case OWN_LAND:
        upgradeLand(curr_place,player);
        break;
    case MINE:
        addPoints(player, curr_place->price);
        break;
    default:
        break;
    }
}

void goRandomSteps(Game *game)
{
    Place *curr_place;
    int steps = randomEx(MIN_DICE_VALUE, MAX_DICE_VALUE);
    Player *player = getCurrentPlayer(game);    

    updatePlayerPos(player,steps,getPlaceNum(game));
    curr_place = getPlaceByIndex(game,getPlayerPosition(player));
    printMap(game);
    arriveAtDifferentPlace(curr_place, player);
    nextPlayer(game);
    printMap(game);
}


typedef void (*POST_PROC)(Place *place, Player *player);

static int isInputYes( char * input ) 
{
    return strcmp("Y",input) == 0 || strcmp("y",input) == 0;
}

static int isInputNo( char * input ) 
{
    return strcmp("N",input) == 0 || strcmp("n",input) == 0;
}

static void ConfirmTransaction( Place *place,  Player *player,  POST_PROC postFunc) 
{
    char input[MAX_INPUT_SIZE];
    printMsg("输入Y/N>");
    for(;;)
    {
        getInput(input, MAX_INPUT_SIZE);

        if(isInputYes(input))
        {
            postFunc(place, player);
            break;
        }
        else if (isInputNo(input))
        {
            break; 
        }
        else
        {
            printMsg("请重新输入Y/N>");
        }
    }
}

static void payForBuyLand(Place *place, Player *player)
{
    player->money -= place->price;
    place->owner = player;
    printf("购买空地成功，花费%d，剩余%d\n",place->price,player->money );
}

static void buyLand(Place *place,Player *player)
{
    if (player->money < place->price)
    {
        printMsg("资金不够，不能购买空地\n");
        return;
    }
    printf("是否购买该处空地(价格%d)",place->price);
    ConfirmTransaction(place, player, payForBuyLand);
}

static void payForUpgradeLand(Place *place, Player *player)
{
    player->money -= place->price;
    place->type++;
    printf("升级成功，花费%d，剩余%d\n",place->price,player->money );
}

static void upgradeLand(Place *place,Player *player)
{
    if (player->money < place->price)
    {
        printMsg("资金不够，不能升级\n");
        return;
    }
    if(isHighestLevel(place))
    {
        return;
    }
    printf("是否升级该处地产(价格%d)",place->price);
    ConfirmTransaction(place, player, payForUpgradeLand);
}

#ifdef __cplusplus
}
#endif
