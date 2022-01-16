#pragma once
#include <string>
#include <list>
#include "prerequisite.h"
#include "ingredient.h"


class Technology
{
private:
    std::string name;
    // std::list<Prerequisite> prerequisites;
    // std::list<Ingredient*> Ingredients;
    // bool enabled;

public:
	Technology(std::string name);
    std::string getName();
};
