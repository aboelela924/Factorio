#include <string>
#include <list>
#include "ingredient.h"
#include "product.h"
#include "technology.h"
#pragma once

class Prerequisite
{
private:
    std::string name;
    int id;
    std::list<Technology*> technologies;  //list of other technologies

public:
	Prerequisite::Prerequisite(std::string name, int id);
    // std::string getName();
    // std::list<Ingredient*> ingredients;
    // std::list<Product*> products;
};