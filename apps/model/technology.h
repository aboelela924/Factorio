#include <string>
#include <list>
#pragma once

class Technology
{
private:
    std::string name;
    std::list<Prerequisite*> prerequisites;
    std::list<Ingredient*> Ingredient;
    // bool enabled;

public:
	Technology(std::string name);
    std::string getName();
};
