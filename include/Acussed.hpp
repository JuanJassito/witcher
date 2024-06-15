#pragma once
#include <string>

class Accused {
private:
    int gender;
    int witch;
    std::string name;
    std::string reasons;

public:
    // Constructor predeterminado
    Accused() : gender(0), witch(0), name("Unknown"), reasons("No reasons provided") {}

    // Constructor con argumentos
    Accused(int gender, int witch, std::string name, std::string reasons) 
        : gender(gender), witch(witch), name(name), reasons(reasons) {}

    // Métodos para obtener datos del acusado
    int getGender() const { return gender; }
    int getWitch() const { return witch; }
    std::string getName() const { return name; }
    std::string getReasons() const { return reasons; }

    std::string getGenderString() const {
        return (gender == 0) ? "Male" : "Female";
    }

    std::string getWitchString() const {
        return (witch == 0) ? "Yes" : "No";
    }
};
