#include <string>
#include <vector>
#include "item.h"
#pragma once

class Recipe
{
private:
    std::string name;
    std::string categorie;
    int energy;
    bool enabled;
    std::vector<Item> ingredients;
    std::vector<Item> products;

public:
	Recipe( 
        std::string name, 
        std::string categorie,
        int energy,
        bool enabled,
        std::vector<Item> ingredients,
        std::vector<Item> products);
    
    std::string getName();
    
    std::vector<Item> getIngredients();
    std::vector<Item> getProducts();

    void setEnabled(bool isEnabled);

};