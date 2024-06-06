#include <iostream>
#include "Words.hpp"

int main() {
    Word wordGenerator("./assets/text/easy.txt");
    Word manName("./assets/text/m_names.txt");
    Word womenName("./assets/text/w_names.txt");

    std::string word = wordGenerator.generateWord();
    size_t length = wordGenerator.getWordLength(word);

    std::string mName = manName.generateWord();
    std::string wName = womenName.generateWord();

    std::cout << "Palabra generada: " << word << std::endl;
    std::cout << "Longitud de la palabra: " << length << std::endl;

    std::cout << mName << std::endl;
    std::cout << wName << std::endl;

    return 0;
}
