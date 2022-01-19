#pragma once

#include <string>
#include <vector>

class Factory
{

public:

	Factory(std::string name, double craftingSpeed, std::vector<std::string> craftingCategories);
	Factory(std::string name, std::string factoryType, int factoryId);
	Factory(const Factory &factory);
	std::string getName();
private:
	std::string name;
	std::string factoryType;
	int factoryId;
	double craftingSpeed;
	std::vector<std::string> craftingCategories;

};