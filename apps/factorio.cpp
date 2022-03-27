

#include "model/technology.h"
#include "model/recipe.h"
#include "model/factory.cpp"

#include "jsonParser.cpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

#include <nlohmann/json.hpp>

#include <string>
#include <limits.h>
#include <unistd.h>
#include "master.h"

  

using json = nlohmann::json;

int main(int argc, char** argv){
	
    Master master = Master(argv[1]);
    // string output;
    // ifstream myfile;
    // ofstream myfile2;

    // string STRING;
    // myfile.open ("test_out.json");


    // myfile >> STRING;
    // cout << STRING;
    // myfile.close();

    return 0;

}
