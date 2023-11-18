#include "Game.h"
#include "Menu.h"



int main(){

    sf::Clock clock;

    Menu myMenu;

    myMenu.runMenu();

    Game myGame;

    myGame.run(clock);


    return 0;
}