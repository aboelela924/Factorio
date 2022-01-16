#include <string>
#include "item.h"

class Product : public Item
{
private:
    int amount;

public:
	Item(std::string name, int amount);
    int getAmount();
};
