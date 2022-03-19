#pragma once

#include <string>
#include <vector>

class Factory
{

public:

	Factory(std::string name, double craftingSpeed, std::vector<std::string> craftingCategories);
	Factory(std::string name, std::string factoryType, int factoryId);
	Factory(const Factory &factory);
	Factory(const Factory&& factory);
	
	std::string getName();
	std::string getFactoryType();
	int getFactoryId();
	double getCraftingSpeed();
	std::vector<std::string>& getCraftingCategories();

	void setCraftingSpeed(double craftingSpeed);
	void setFactoryId(int id);
	void setFactoryType(std::string factoryType);


private:
	std::string name;
	std::string factoryType;
	int factoryId;
	double craftingSpeed;
	std::vector<std::string> craftingCategories;

};