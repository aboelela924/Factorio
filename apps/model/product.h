#include <string>
#include "item.h"
#pragma once

class Product : public Item
{
private:
    int amount;

public:
	Product(std::string name, int amount);
    int getAmount();
};
