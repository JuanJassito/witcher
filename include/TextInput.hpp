#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

class TextInput
{
private:
    sf::String text;
    int maxLenght = 10;
public:
    TextInput(/* args */) {}
    TextInput(int maxLenght){
        this->maxLenght = maxLenght;
    }
    ~TextInput() {}
    string GetText(){
        return this->text.toAnsiString();
    }
    void OnInput(sf::Uint32 character){
        if (character < 128)
        {
            if (this->text.getSize() < this->maxLenght){
                this->text += text;
            }
        }
    }

};