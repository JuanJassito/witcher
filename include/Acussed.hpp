#include "Generator.hpp"
#include <string>

class Acussed{
private:
    textGenerator generate;
    numGenerator genSex;
    std::string name;
    int sex; 

public:
    Acussed(const std::string& filename) : generate(filename) {}

    std::string generateName(){
        return generate.readText();
    }
    
};