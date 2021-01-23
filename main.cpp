#include <iostream>

#include "texte.h"
#include "audio.h"

using namespace std;

void encodeur_decodeur(int argc, char **argv)
{
    if (argv[1][0] != 'E' and argv[1][0] != 'D')
    {
        throw string("Le deuxième argument doit être E pour un encodage (français vers morse), D pour un décodage (morse vers français)");
    }
    else if (argv[1][0] == 'E')
    {
        string a_traduire = "";
        for (int i = 2; i < argc; i++)
        {
            a_traduire += (string)argv[i];
            a_traduire += " ";
        }
        texte txt('F', a_traduire);
        txt.encode();
        audio aud;
        aud.m_to_s(txt.morse_getter());
    }
    else if (argv[1][0] == 'D')
    {
        audio aud;
        aud.s_to_m(argv[2]);
        string mrs = aud.morse_texte;
        texte txt('M', aud.morse_texte);
        txt.decode();
        cout<<txt.francais_getter()<<endl;
    }
}

int main(int argc, char **argv)
{
    try
    {
        encodeur_decodeur(argc, argv);
    }
    catch(string const& chaine)
    {
        cerr << chaine << endl;
    }
    return 0;
}