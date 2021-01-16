#include <iostream>

#include "../include/texte.h"

using namespace std;

texte::texte(){}

texte::~texte(){}

void texte::morse_setter(string mrs) // le code morse doit finir par un espace
{
    morse = mrs;
}

string texte::morse_getter()
{
    return morse;
}

void texte::francais_setter(string fr)
{
    francais = fr;
}

string texte::francais_getter()
{
    return francais;
}

void texte::encode()
{
    for (int i = 0; francais[i] != 0; i++)
    {
        morse += fr_to_m[francais[i]];
        morse += string(" ");
    }
}

void texte::decode(){
    for (int i = 0; morse[i] != 0; i++)
    {   
        string car = "";
        for (int j = i; (morse[j] != 0) and (morse[j] != ' '); j++)
        {
            car += morse[j];
            //cout<<car;
            i = j;
        }
        francais += m_to_fr[car];
        //cout<<morse<<endl;
    }
}