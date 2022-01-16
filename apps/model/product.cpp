#include "product.h"

Product::Product(std::string name, int amount) 
    :Item{ name }, amount(amount) { };

int Product::getAmount() {
	return this->amount;
}