#include <iostream>

#include "texte.h"
#include "audio.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argv[1][0] == 'E')
    {
        texte txt;
        txt.francais_setter(argv[2]);
        txt.encode();
        audio aud;
        aud.m_to_s(txt.morse_getter());
    }
    else if (argv[1][0] == 'D')
    {
        string mrs = "";
        for (int i = 2; i < argc; i++)
        {
            mrs += (string)argv[i],
            mrs += " ";
        }
        texte txt;
        txt.morse_setter(mrs);
        txt.decode();
        cout<<txt.francais_getter()<<endl;
    }
    else
    {
        cout<<"Le deuxième argument doit être E pour un encodage (français vers morse), D pour un décodage (morse vers français)"<<endl;
    }

    audio test;

    test.s_to_m("traduction.wav");

    return 0;
}