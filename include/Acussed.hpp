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
    std::string reasons;

public:
    Accused(numGenerator& ng, imageGenerator& ig) {
        gender = ng.generate();
        std::string nameFile = gender == 0 ? "./assets/text/m_names.txt" : "./assets/text/w_names.txt";
        textGenerator tg(nameFile);
        name = tg.readText();
        imagePath = ig.generateImage(gender);
        reasons = textGenerator("./assets/text/reasons.txt").readText();
    }

    std::string getName() const {
        return name;
    }

    int getGender() const {
        return gender;
    }

    std::string getGenderString() const {
        return gender == 0 ? "Hombre" : "Mujer";
    }

    std::string getImagePath() const {
        return imagePath;
    }

    std::string getReason() const {
        std::cout<<reasons<<std::endl;
        return reasons;
    }
};