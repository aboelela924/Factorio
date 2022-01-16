#include "item.h"
#include <string>


Item::Item(std::string name) : name(name) {};

std::string Item::getName() {
	return this->name;
}
