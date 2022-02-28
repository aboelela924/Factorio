
#include "model/event.h"
#include "model/researchEvent.h"
#include "model/buildFactoryEvent.h"
#include "model/destoryFactoryEvent.h"
#include "model/startFactoryEvent.h"
#include "model/stopFactoryEvent.h"
#include "model/victoryEvent.h"
#include "model/technology.h"
#include "model/ingredient.h"
#include "model/recipe.h"
#include "model/product.h"
#include "model/prerequisite.h"
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

    std::string getexepath()
    {
        char result[ PATH_MAX ];
        ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
        return std::string( result, (count > 0) ? count : 0 );
    }

// #ifdef __linux__ 
//     // Linux code goes here
//     std::string getexepath()
//     {
//         char result[ PATH_MAX ];
//         ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
//         return std::string( result, (count > 0) ? count : 0 );
//     }

// #elif _WIN32
//     // windows code goes here

//     #include <Windows.h>
//     #include <string>

// std::string GetCurrentDirectory()
// {
// 	char buffer[MAX_PATH];
// 	GetModuleFileNameA(NULL, buffer, MAX_PATH);
// 	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	
// 	return std::string(buffer).substr(0, pos);
// }
// #else

// #endif

using json = nlohmann::json;

int main(int argc, char** argv){

    //Ahmed Path
    std::string local_path = getexepath();
    std::string delimiter = "out";
    local_path = local_path.substr(0, local_path.find(delimiter)); // token is "scott"
    std::string path=local_path+"jsons/example_1.json";
    std::cout << "PATH  : "<< path << std::endl;

    //Omar path
    // std::string local_path = getexepath();
    // std::string delimiter = "Factorio";
    // local_path = local_path.substr(0, local_path.find(delimiter));
    // // std::string path=local_path+"/Factorio/jsons/example_1.json";
    // std::string path=local_path+"/Factorio/data/factorio-data/recipe.json";

    Master master = Master(local_path);

    

    return 0;

}
