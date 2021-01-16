#include <iostream>

#include "texte.h"

using namespace std;

int main()
{
    texte txt;
    txt.morse_setter(". _. ._ / ._ _ .");
    txt.decode();
    cout<<txt.francais_getter();
    return 0;
}