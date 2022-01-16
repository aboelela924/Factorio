#include <string>
#include <list>
#include "ingredient.h"
#include "product.h"
#pragma once

class Recipe
{
private:
    std::string name;
    std::string categorie;
    int energy;
    bool enabled;


public:
	Recipe(std::string name, std::string categorie,int energy,bool enabled);
    std::string getName();
    std::list<Ingredient*> ingredients;
    std::list<Product*> products;
};