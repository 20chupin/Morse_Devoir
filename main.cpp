#include <iostream>

#include "texte.h"
#include "audio.h"

using namespace std;

void encodeur_decodeur(int argc, char **argv)
{
    if (argc ==  1)
    {
        throw string("Pour un encodage (français vers morse): \nLe premier argument doit être E \nLe deuxième argument doit être une phrase composée de lettre majuscules, et/ou des caractères '.', ',', '?' \n\nPour un décodage (morse vers français): \nLe premier argument doit être D \nLe deuxième argument doit être le nom du fichier wave à analyser" );
    }
    else if (argv[1][0] != 'E' and argv[1][0] != 'D')
    {
        throw string("Pour un encodage (français vers morse): \nLe premier argument doit être E \nLe deuxième argument doit être une phrase composée de lettre majuscules, et/ou des caractères '.', ',', '?' \n\nPour un décodage (morse vers français): \nLe premier argument doit être D \nLe deuxième argument doit être le nom du fichier wave à analyser" );
    }

    // Encodage
    else if (argv[1][0] == 'E')
    {
        // On récupère la phrase à traduire
        string a_traduire = "";
        for (int i = 2; i < argc; i++)
        {
            a_traduire += (string)argv[i];
            a_traduire += " ";
        }
        
        // Encodage en morse écrit
        texte txt('F', a_traduire);
        txt.encode();

        //Encodage en morse audio dans traduction.wav
        audio aud;
        aud.m_to_s(txt.morse_getter());
        cout<<"La traduction en morse se trouve dans le fichier audio traduction.wav"<<endl;
    }

    //Décodage
    else if (argv[1][0] == 'D')
    {
        //Décodage en morse écrit (ne marche qu'avec exemple prof)
        audio aud;
        aud.s_to_m(argv[2]);
        string mrs = aud.morse_texte_getter();

        //Décodage en français écrit
        texte txt('M', aud.morse_texte_getter());
        txt.decode();
        cout<<txt.francais_getter()<<endl;
    }
}

void e_d_gestion_d_erreur(int argc, char **argv)
{
    try
    {
        encodeur_decodeur(argc, argv);
    }
    catch(string const& chaine)
    {
        cerr << chaine << endl;
    }
}

void tests()
{
    // Test de la partie traduction écrite
    cout << "Test de la partie traduction écrite :" << endl;
    string ascii_string_ori = "HELLO WORLD";
    string ascii_string = ascii_string_ori;
    string morse_string;

    // Affichage valeur de départ
    cout << "ascii : " << ascii_string << endl;

    // Encodage
    texte F('F', ascii_string);
    F.encode();
    morse_string = F.morse_getter();
    cout << "encodage morse : " << morse_string << endl;

    // Décodage
    texte M('M', morse_string);
    M.decode();
    ascii_string = M.francais_getter();
    cout << "decodage morse : " << ascii_string << endl;

    // Test
    if (ascii_string == ascii_string_ori)
    {
        cout << "Peut-être ok..." << endl << endl;
    }
    else
    {
        cout << "nok" << endl << endl;
    }

    // Test décodage complet
    cout << "Test du décodage complet de 'exemple_prof.wav' :" << endl;
    char* exe = "exe";
    char* E_or_D = "D";
    char* a_traduire = "exemple_prof.wav";
    char* argv[3] = {exe, E_or_D, a_traduire};
    cout << "'e_d_gestion_d_erreur' devrait afficher 'SOS SOS' et il affiche : " << endl;
    e_d_gestion_d_erreur(3, argv);
    cout << endl;

    // Test encodage complet
    cout << "Test de l'encodage complet de 'HELLO WORLD.' :" << endl;
    E_or_D = "E";
    a_traduire = "HELLO WORLD.";
    argv[1] = E_or_D;
    argv[2] = a_traduire;
    e_d_gestion_d_erreur(3, argv);
    cout << endl;
}

int main(int argc, char **argv)
{
    // Commenter une des deux lignes suivantes
    //tests();
    e_d_gestion_d_erreur(argc, argv);
    return 0;
}