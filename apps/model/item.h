#include <string>
#pragma once

class Item {

protected:
	std::string name;
	std::string type;
	int amount;
public:

	Item(std::string name, std::string type) ;
	Item(std::string name, std::string type, int amount);
	Item(std::string name, int amount);
	
	std::string getName();
	void decreaseAmountBy(int value);
	void increaseAmoutnBy(int value);
	int getAmount();
	
};
