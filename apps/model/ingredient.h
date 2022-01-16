#include <string>
#include "item.h"

class Ingredient : public Item
{
private:
    int amount;

public:
	Ingredient(std::string name, int amount);
    int getAmount();
};
