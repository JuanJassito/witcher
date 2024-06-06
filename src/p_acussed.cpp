#include <iostream>
#include "Acussed.hpp"

using namespace std;

int main(){
    Acussed man("./assets/text/m_names.txt");
    Acussed woman("./assets/text/w_names.txt");

    string mName = man.generateName();
    string wName = woman.generateName();

    cout<<mName<<endl;
    cout<<wName<<endl;

    return 0;
}