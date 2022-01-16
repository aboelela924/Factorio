#include "recipe.h"
#include <iostream>
#include <string>


using namespace std;

Recipe::Recipe(std::string name): name(name) {};

std::string Recipe::getName() {
	return this->name;
}
