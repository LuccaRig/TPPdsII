#include "Item.h"

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

Item::Item(int x, int y)  
{
    item_type_ = returnsRandomItem();
    item_position_x_ = x;
    item_position_y_ = y;
}

string Item::returnsRandomItem() 
{
    map<int, string> item_n;
    item_n[1] = "heal";
    item_n[2] = "heal";
    item_n[3] = "dmgBuff";
    item_n[4] = "spellBuff";

    srand((unsigned) time(NULL));
	int random = 1 + rand()%10;

    if (random <= 4) 
    {
        return item_n[random];
    }
    else 
    {
        return "empty";
    }
}