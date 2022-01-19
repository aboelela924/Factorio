
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
    std::string local_path = getexepath();
    std::string delimiter = "out";
    local_path = local_path.substr(0, local_path.find(delimiter)); // token is "scott"
    std::string path=local_path+"/Factorio/jsons/example_1.json";
    std::cout << path << std::endl;
    /*std::ifstream i1(path);
    json j1;
    i1 >> j1;
    std::cout << j1 << std::endl;
    std::cout<<std::endl;
    std::cout << std::setw(2) << j1 << std::endl;*/
    
    

    string challengePath = local_path + "/data/factorio-data/example-challenge.json";
    JsonParser::readChallenge(challengePath);
    /*string factoryPath = local_path + "/data/factorio-data/factory.json";
    JsonParser::readFactories(factoryPath);*/

    /*
    AHMED CODE !
    */
    // Event* researchEvent = new ResearchEvent(1.5, "Space ship");
    // researchEvent->run();
    // Event* buildFactoryEvent = new BuildFactoryEvent(2.5, 1, "mold", "Mold removal");
    // buildFactoryEvent->run();
    // Event* destoryFactoryEvent = new DestoryFactoryEvent(3.5, 1);
    // destoryFactoryEvent->run();
    // Event* startFactoryEvent = new StartFactoryEvent(4.5, 1, "Killer recipe");
    // startFactoryEvent->run();
    // Event* stopFactoryEvent = new StopFactoryEvent(5.5, 1);
    // stopFactoryEvent->run();
    // Event* victoryEvent = new VictoryEvent(6.5);
    // victoryEvent->run();

    /*Technology* techno = new Technology("TechnoName");
    std::cout<<techno->getName()<<std::endl;

    Ingredient* ingr = new Ingredient("IngrName",5);
    std::cout<<ingr->getName()<<std::endl;
    std::cout<<ingr->getAmount()<<std::endl;

    Product* prod = new Product("prodName",99);
    std::cout<<prod->getName()<<std::endl;
    std::cout<<prod->getAmount()<<std::endl;

    Recipe* recp=new Recipe("RecipName","recipCateg",5,false);
    recp->ingredients.push_back(ingr);

    Prerequisite* prereq= new Prerequisite("prereqName",56);*/
    


    //Recipe(std::string name, std::string categorie,int energy,bool enabled);





    

    

    int x;
    cin >> x;
//------------------------------------------------------
//Writing to json-format
//------------------------------------------------------   
/*
    std::stringstream ss;
    ss << R"({
        "number":23,
        "string":"Hello World!",
        "array":[1,2,3,4,5]
        })";

    json j2;
    ss >> j2;

    json jTest = {
        {"pi",3.141},
        {"happy",true},
        {"name","Malte"},
        {"nothing",nullptr},
        {"answer",{
                      {"everything",42}
        }}
    };
    std::cout << "Version 1: stringstream" << std::endl;
    std::cout << std::setw(2) <<j2 <<std::endl;
    std::cout << "Version 2: Writing directly to json" << std::endl;
    std::cout << std::setw(2) << jTest <<std::endl;
*/
//------------------------------------------------------
//Iterate over elements
//------------------------------------------------------
/*
    std::ifstream i2("../jsons/example_2.json");
    json j3;
    i2 >> j3;
    std::cout<<"Print out example_2.json"<<std::endl;
    std::cout<<std::setw(2) << j3 << std::endl;
    std::cout<<std::endl;

    //Version 1
    std::cout<<"Version 1: Iterator"<<std::endl;
    for(json::iterator it = j3.begin();it != j3.end();++it){
        std::cout<< *it <<std::endl;
    }
    std::cout<<std::endl;

    //Version 2
    std::cout<<"Version 2: For each Loop"<<std::endl;
    for(auto& element : j3){
        std::cout<< element << std::endl;
    }
    std::cout<<std::endl;

    //Version 3
    std::cout<<"Version 3: Iterator key/value"<<std::endl;
    for(json::iterator it = j3.begin();it != j3.end();++it){
        std::cout<<"Key: "<< it.key()<<" Value: "<<it.value() <<std::endl;
    }
    std::cout<<std::endl;

    //Version 4
    std::cout<<"Version 4: For each Loop key/value"<<std::endl;
    for(auto& element : j3.items()){
        std::cout<<"Key: "<< element.key() << " Value: "<< element.value() << std::endl;
    }
*/
//------------------------------------------------------
//Search for element in JSON
//------------------------------------------------------
/*
    std::ifstream i3("../jsons/example_2.json");
    json j4;
    i3 >> j4;
    std::cout<<"Print out example_2.json"<<std::endl;
    std::cout<<std::setw(2) << j4 << std::endl;
    std::cout<<std::endl;    
    
    if(j4.find("water") != j4.end()){
        std::cout<<"Found Water!"<<std::endl;
    }
*/
//------------------------------------------------------
//Write JSON output
//------------------------------------------------------
/*
    std::ifstream i4("../jsons/example_2.json");
    json j5;
    i4 >> j5;
    std::cout<<"Print out example_2.json"<<std::endl;
    std::cout<<std::setw(2) << j5 << std::endl;
    std::cout<<std::endl;

    std::ofstream o("../jsons/new_json.json");
    o << std::setw(2) << j5 << std::endl;
*/

    return 0;

}
