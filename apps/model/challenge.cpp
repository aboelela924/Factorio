#include "challenge.h"

Challenge::Challenge(std::vector<Factory> initalFactories, 
	std::vector<Item> goalItems, 
	std::vector<Item> initialItems)
	: initalFactories(initalFactories), 
	goalItems(goalItems),
	initialItems(initialItems) {}
