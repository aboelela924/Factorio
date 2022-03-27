#include "technology.h"
#include <iostream>
#include <string>


using namespace std;


Technology::Technology(std::string name, 
	std::vector<std::string> prerequisites,
	std::vector<Item> ingredients, 
	std::vector<std::string> effectes, 
	bool enabled)
	: name(name), prerequisites(prerequisites), 
	ingredients(ingredients), effectes(effectes), 
	enabled(enabled)
{
}

std::string Technology::getName() {
	return this->name;
}

std::vector<std::string> Technology::getPrerequisites()
{
	return this->prerequisites;
}

std::vector<Item> Technology::getIngredients()
{
	return this->ingredients;
}

std::vector<std::string> Technology::getEffects()
{
	return this->effectes;
}

bool Technology::getEnabled()
{
	return this->enabled;
}

void Technology::setEnabled(bool isEnabled)
{
	this->enabled = isEnabled;
}
