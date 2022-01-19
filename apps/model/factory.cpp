#include "factory.h"
#include "factory.h"

Factory::Factory(std::string name, double craftingSpeed, std::vector<std::string> craftingCategories)
: name(name), craftingSpeed(craftingSpeed), craftingCategories(craftingCategories) {}

Factory::Factory(std::string name, std::string factoryType, int factoryId)
	: name(name), factoryType(factoryType), factoryId(factoryId)
{
}

Factory::Factory(const Factory& factory)
{
	this->name = factory.name;
	this->craftingSpeed = factory.craftingSpeed;
	this->craftingCategories = factory.craftingCategories;

}

std::string Factory::getName()
{
	return this->name;
}
