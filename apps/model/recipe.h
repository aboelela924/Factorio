#include <string>
#include <vector>
#include "item.h"
#pragma once

class Recipe
{
private:
    int energy;
    bool enabled;
    std::vector<Item> ingredients;
    std::vector<Item> products;

public:
    
    std::string name;
    std::string categorie;

	Recipe( 
        std::string name, 
        std::string categorie,
        int energy,
        bool enabled,
        std::vector<Item> ingredients,
        std::vector<Item> products);
    
    bool operator==(const Recipe r) const;

    std::string getName();
    std::string getCategory();
    int getEnergy();
    
    std::vector<Item> getIngredients();
    std::vector<Item> getProducts();

    bool getEnbaled();
    void setEnabled(bool isEnabled);

};