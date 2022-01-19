#include "item.h"
#include <string>


Item::Item(std::string name) : name(name) {}
Item::Item(std::string name, int amount) : name(name), amount(amount)
{
}
;

std::string Item::getName() {
	return this->name;
}

int Item::getAmount()
{
	return this->amount;
}
