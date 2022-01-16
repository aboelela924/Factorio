#include "ingredient.h"

Ingredient::Ingredient(std::string name, int amount) 
    :Item{ name }, amount(amount) { };


int Ingredient::getAmount() {
	return this->amount;
}
