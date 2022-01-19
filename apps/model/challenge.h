#pragma once

#include <vector>

#include "item.h"
#include "factory.h"

class Challenge
{
public:
	Challenge(std::vector<Factory> initalFactories, 
		std::vector<Item> goalItems, 
		std::vector<Item> initialItems);

private:
	std::vector<Factory> initalFactories;
	std::vector<Item> goalItems;
	std::vector<Item> initialItems;
};

