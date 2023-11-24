#ifndef ITEMSINBOARD_H_
#define ITEMSINBOARD_H_

#include <vector>

#include "Item.h"

class ItemsInBoard {
  public:
  std::vector<Item*> returnItemVector();

  Item* getItemInPosition(int x, int y);

  private:
  std::vector<Item*> items_;
};

#endif // ITEMSINBOARD_H_ 