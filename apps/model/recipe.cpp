	#include "recipe.h"
#include <iostream>
#include <string>

Recipe::Recipe(std::string name, 
	std::string categorie,
	int energy,
	bool enabled, 
	std::vector<Item> ingredients,
	std::vector<Item> products)
:name(name),
categorie(categorie),
energy(energy),
enabled(enabled),
ingredients(ingredients), 
products(products) {}


bool Recipe::operator==(const Recipe r) const
{
	return r.name == this->name;
}



std::string Recipe::getName() {
	return this->name;
}

std::string Recipe::getCategory()
{
	return this->categorie;
}

int Recipe::getEnergy()
{
	return this->energy;
}

std::vector<Item> Recipe::getIngredients()
{
	return this->ingredients;
}

std::vector<Item> Recipe::getProducts()
{
	return this->products;
}

bool Recipe::getEnbaled()
{
	return this->enabled;
}

void Recipe::setEnabled(bool isEnabled)
{
	this->enabled = isEnabled;
}
