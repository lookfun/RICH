#include "rich.h"
#include "map.h"
#include "player.h"
#include "printMap.h"
#include "command.h"

void gameStart()
{
    Game *game = createGame();

    initializeMoney(game);
    initializePlayer(game);
    initMap(game);
    printMap(game);
    run(game);

    destroyGame(game);
}

int main()
{
    gameStart();
    return 0;
}
