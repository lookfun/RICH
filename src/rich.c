#include "rich.h"
#include "util.h"

Game * createGame()
{
    Game *game = (Game *) malloc(sizeof(Game));
    memset(game,0,sizeof(Game));
    return game;
}
void destroyGame(Game *game)
{
    free(game);
}

void setInitMoney(int money, Game *game)
{
    game->init_money = money;
}

int getInputMoney()
{
    char input[MAX_INPUT_SIZE];
    printMsg("请输入初始资金(1000~50000)，直接回车，默认10000:\n");
    getInput(input,MAX_INPUT_SIZE);
    if (strlen(input) == 0)
    {
        return DEFAULT_MONEY;
    }
    return str2int(input);
}
void initializeMoney(Game *game)
{
    int money = -1;
    game->init_money = DEFAULT_MONEY; 
    do 
    {
        money = getInputMoney(); 
    } while (money>MAX_INIT_MONEY || money < MIN_INIT_MONEY);
  
    setInitMoney(money,game);
}





