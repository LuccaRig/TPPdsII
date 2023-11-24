#include "Game.h"
#include "Menu.h"



int main(){
    srand((unsigned) time(NULL));
    
    Menu myMenu;

    myMenu.runMenu();

    return 0;
}