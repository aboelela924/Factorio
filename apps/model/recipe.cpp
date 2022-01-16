#include "recipe.h"
#include <iostream>
#include <string>

Recipe::Recipe(std::string name, std::string categorie,int energy,bool enabled)
:name(name),categorie(categorie),energy(energy),enabled(enabled) {};

std::string Recipe::getName() {
	return this->name;
}