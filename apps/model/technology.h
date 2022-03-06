#pragma once
#include <string>
#include <vector>
#include "item.h"

class Technology
{
private:
    std::string name;
    std::vector<std::string> prerequisites;
    std::vector<Item> ingredients;
    std::vector<std::string> effectes;
    bool enabled;

public:
	Technology(std::string name, 
        std::vector<std::string> prerequisites,
        std::vector<Item> ingredients,
        std::vector<std::string> effectes,
        bool enabled);
    
    std::string getName();
    std::vector<std::string> getPrerequisites();
    std::vector<Item> getIngredients();
    std::vector<std::string> getEffects();
    bool getEnabled();
};
