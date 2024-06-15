#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>
#include <string>
#include <filesystem>
#include "Generator.hpp"

class Accused {
private:
    std::string name;
    int gender;
    std::string imagePath;
    std::string reason;
    int witch;

public:
    Accused(numGenerator& ng, imageGenerator& ig) {
        gender = ng.generate();
        witch = ng.generate();

        std::string nameFile = gender == 0 ? "./assets/text/m_names.txt" : "./assets/text/w_names.txt";
        textGenerator nameGen(nameFile);
        name = nameGen.readText();

        imagePath = ig.generateImage(gender);

        textGenerator reasonGen("./assets/text/reasons.txt");
        reason = reasonGen.readText();
    }

    std::string getName() const {
        return name;
    }

    int getGender() const {
        return gender;
    }

    std::string getGenderString() const {
        return gender == 0 ? "Man" : "Woman";
    }

    std::string getImagePath() const {
        return imagePath;
    }

    std::string getReason() const {
        return reason;
    }

    int getWitch() const {
        return witch;
    }

    std::string getWitchString() const {
        return witch == 0 ? "Witch" : "Not Witch";
    }
};
