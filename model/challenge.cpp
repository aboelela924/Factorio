#include "challenge.h"

Challenge::Challenge(std::vector<Factory> initalFactories, 
	std::vector<Item> goalItems, 
	std::vector<Item> initialItems)
	: initalFactories(initalFactories), 
	goalItems(goalItems),
	initialItems(initialItems) {}

std::vector<Factory> Challenge::getFactories()
{
	return this->initalFactories;
}

std::vector<Item> Challenge::getGoalItems()
{
	return this->goalItems;
}

std::vector<Item> Challenge::getInitialItems()
{
	return this->initialItems;
}
