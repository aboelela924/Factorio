#include "item.h"
#include <string>


Item::Item(std::string name, std::string type) : name(name), type(type), amount(0) {}
Item::Item(std::string name, std::string type, int amount) : name(name), type(type), amount(amount) {}
Item::Item(std::string name, int amount) : name(name), amount(amount) {}


std::string Item::getName() {
	return this->name;
}

void Item::decreaseAmountBy(int value)
{
	this->amount -= value;
}

void Item::increaseAmoutnBy(int value)
{
	this->amount += value;
}

int Item::getAmount()
{
	return this->amount;
}
