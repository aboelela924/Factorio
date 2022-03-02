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
products(products) {};

std::string Recipe::getName() {
	return this->name;
}