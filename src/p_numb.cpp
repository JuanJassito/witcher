#include <iostream>
#include "Generator.hpp"
using namespace std;

int main(){
    numGenerator numGen(1,15);
    numGenerator numGen2(0,5);

    int random1 = numGen.generate();
    int random2 = numGen2.generate();
    int random3 = numGen2.generate();

    cout<<random1<<endl;
    cout<<random2<<endl;
    cout<<random3<<endl;

    return 0;
}