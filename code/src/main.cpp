#include "Game.h"
#include "Settings.h"
#include <stdlib.h>
int main(void)
{
    Game game{  settings::screenWidth, 
                settings::screenHeight, 
                "Vydia", 
                settings::fps};
    game.Execute();
    return 0;
}