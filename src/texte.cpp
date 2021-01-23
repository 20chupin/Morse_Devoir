#include <iostream>

#include "../include/texte.h"

using namespace std;

texte::texte(char M_or_F, string txt)
{
    if (M_or_F == 'M')
    {
        morse = txt;
    }
    else if (M_or_F == 'F')
    {
        francais = txt;
    }
}

texte::~texte(){}

string texte::morse_getter()
{
    return morse;
}

string texte::francais_getter()
{
    return francais;
}

void texte::encode()
{
    morse = "";
    for (int i = 0; francais[i] != 0; i++)
    {
        morse += fr_to_m[francais[i]];
        morse += string(" ");
    }
}

void texte::decode()
{
    francais = "";
    for (int i = 0; morse[i] != 0; i++)
    {   
        string car = "";
        for (int j = i; (morse[j] != 0) and (morse[j] != ' '); j++)
        {
            car += morse[j];
            i = j;
        }
        francais += m_to_fr[car];
    }
}