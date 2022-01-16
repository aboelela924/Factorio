#include <string>

class Recipe
{
private:
    std::string name;
    std::string categorie;
    int energy;
    bool enabled;
    //list if ingredient
    //list of product


public:
	Recipe(std::string name);
    std::string getName();
};
