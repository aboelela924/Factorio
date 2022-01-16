#include "technology.h"
#include <iostream>
#include <string>


using namespace std;

Technology::Technology(std::string name): name(name) {};

std::string Technology::getName() {
	return this->name;
}
