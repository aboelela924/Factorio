#include <string>
#pragma once

class Item {

protected:
	std::string name;
	int amount;
public:

	Item(std::string name) ;
	Item(std::string name, int amount);
	
	std::string getName();
	int getAmount();
	/*{
		return this->timestamp;
	}*/
};
