#include "factory.h"
#include "factory.h"

Factory::Factory(std::string name, double craftingSpeed, std::vector<std::string> craftingCategories)
: name(name), craftingSpeed(craftingSpeed), craftingCategories(craftingCategories), factoryId(-1), 
requiredRunningTime(0) {}

Factory::Factory(std::string name, std::string factoryType, int factoryId)
	: name(name), factoryType(factoryType), factoryId(factoryId), requiredRunningTime(0)
{
}

Factory::Factory(const Factory& factory)
{
	this->name = factory.name;
	this->craftingSpeed = factory.craftingSpeed;
	this->craftingCategories = factory.craftingCategories;
	this->factoryId = factory.factoryId;
	this->factoryType = factory.factoryType;

}

Factory::Factory(const Factory&& factory)
{
	this->name = factory.name;
	this->craftingSpeed = factory.craftingSpeed;
	this->craftingCategories = factory.craftingCategories;
	this->factoryId = factory.factoryId;
	this->factoryType = factory.factoryType;
}

std::string Factory::getName()
{
	return this->name;
}

std::string Factory::getFactoryType()
{
	return this->factoryType;
}

int Factory::getFactoryId()
{
	return this->factoryId;
}

double Factory::getCraftingSpeed()
{
	return this->craftingSpeed;
}

std::vector<std::string>& Factory::getCraftingCategories()
{
	return this->craftingCategories;
}

void Factory::setCraftingSpeed(double craftingSpeed)
{
	this->craftingSpeed = craftingSpeed;
}

void Factory::setFactoryId(int id)
{
	this->factoryId = id;
}

double Factory::getFactoryRequiredTime()
{
	return this->requiredRunningTime;
}

void Factory::increaseRequiredTimeBy(double time)
{
	requiredRunningTime += time / craftingSpeed;
}

void Factory::decreaseRequiredTimeBy(double time)
{
	requiredRunningTime -= time / craftingSpeed;
}
