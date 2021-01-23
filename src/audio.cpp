#include <iostream>
#include <fstream>
#include <cmath>

#include "../include/audio.h"

using namespace std;

audio::audio(){}
    
audio::~audio(){}

string audio::morse_texte_getter()
{
    return morse_texte;
}

void audio::m_to_s(string mrs)
{   
    double two_pi = 6.283185307179586476925286766559;
    // Variables correspondant aux caractéristiques du fichier à entrer dans le Header
    const char* FileInfos = "RIFF----WAVEfmt ";
    uint32_t BlocSize = 16;
    uint16_t AudioFormat = 1;
    uint16_t NbrCanaux = 1;
    uint32_t Frequence = 44100;
    uint32_t BytePerSec = 176400;
    uint16_t BytePerBloc = 4;
    uint16_t BitsPerSample = 16;
    const char* Data = "data----";

    ofstream f;
    
    f.open("traduction.wav", ofstream::binary); // Crée et ouvre le fichier en binaire
    
    if (f.is_open())
    {
        // Ecriture de l'en-tête
        f << FileInfos;
        f.write(reinterpret_cast<char *>(&BlocSize), sizeof(BlocSize));
        f.write(reinterpret_cast<char *>(&AudioFormat), sizeof(AudioFormat));
        f.write(reinterpret_cast<char *>(&NbrCanaux), sizeof(NbrCanaux));
        f.write(reinterpret_cast<char *>(&Frequence), sizeof(Frequence));
        f.write(reinterpret_cast<char *>(&BytePerSec), sizeof(BytePerSec));
        f.write(reinterpret_cast<char *>(&BytePerBloc), sizeof(BytePerBloc));
        f.write(reinterpret_cast<char *>(&BitsPerSample), sizeof(BitsPerSample));
        size_t data_chunk_pos = f.tellp();
        f << Data;
        
        // Variables correspondant aux caractéristiques du son
        constexpr double amplitude = 32760; // Correspond au volume
        double frequency = 440.0; // La 440

        // Variables de construction de fichier son
        int c = 0; // Compteur du nombre de sample écrits
        int son = 1; // son indique si on doit écrire du son (1) ou du silence (0)
        float imp = ti; // imp correspond au temps de l'impulsion de silence ou de son

        //Parcours de la chaine de caractère en morse
        for (int n = 0; mrs[n] != 0; n++)
        {
            // Analyse du caractère mrs[n]
            if (mrs[n] == '.')
            {
                son = 1;
                imp = ti;
            }
            else if (mrs[n] == '_')
            {
                son = 1;
                imp = taah;      
            }
            else if (mrs[n] == '/')
            {
                son = 0;
                imp = 5*ti; // Avec un blanc de durée ti avant et un après, le silence sera bien d'une durée de 7 ti
            }
            else if (mrs[n] == ' ')
            {
                son = 0;
                imp = ti; // Avec un blanc de durée ti avant et un après, le silence sera bien d'une durée de 3 ti
            }

            // Impulsion de son ou de silence en fonction de la variable son, de durée imp
            for (int i = 0; i < Frequence * imp ; i++)
            {
                double value = sin((two_pi * c * 440) / Frequence);
                int value_int = (int)(value * amplitude * son);
                f.write(reinterpret_cast<char *>(&value_int), 2);
                c++;
            }

            // Silence de durée ti pour suivre un son ou compléter une durée de silence
            for (int i = 0; i < Frequence * ti ; i++)
            {
                int value_int = 0;
                f.write(reinterpret_cast<char *>(&value_int), 2);
                c++;
            }
        }

        // Compléter la taille du fichier dans l'en-tête
        size_t file_length = f.tellp();

        f.seekp(data_chunk_pos + 4);
        uint8_t un = file_length - data_chunk_pos + 8;
        f.write(reinterpret_cast<char *>(&un), 4 );

        f.seekp(4);
        uint8_t deux = file_length - 8;
        f.write(reinterpret_cast<char *>(&deux), 4 ); 

        f.close();
    }    
}

void audio::s_to_m(string file_name)
{
    string morse="";

    ifstream f;

    f.open(file_name, ios::binary);

    if (f.is_open())
    {
        // On récupère la taille du fichier
        f.ignore(40);
        uint32_t taille;
        f.read(reinterpret_cast<char *>(&taille), sizeof (taille));

        // On fait une première lecture du fichier pour obtenir la taille du tableau qui va stocker la durée des sons et des silences
        int taille_tableau = 0; // Taille initialisée à 0

        uint32_t var = 1; // Variable qui récupère la valeur du sample
        bool boucle = true; // variable qui sert à continuer les boucles qui lisent les sons si un sample vaut 0

        for (; f.tellg() < taille ;)
        {
            taille_tableau++;
            for (; f.tellg() < taille and boucle ;)
            {
                f.read(reinterpret_cast<char *>(&var), sizeof (var));
                if (var == 0 and f.tellg() < taille) // Si un sample est nul on regarde si le suivant aussi est nul, si c'est le cas, boucle devient false car on passe à un silence
                {
                    f.read(reinterpret_cast<char *>(&var), sizeof (var));
                    if (var == 0)
                    {
                        boucle = false;
                    }
                }
            }
            // On vient de lire un son, par la suite on va lire un silence
            boucle = true;

            for (; f.tellg() < taille and var == 0 ;)
            {
                f.read(reinterpret_cast<char *>(&var), sizeof (var));
            }
        }

        // Tableaux à remplir des durées (en nombre de sample) des sons et des silences
        int uns[taille_tableau] = {0};
        int zeros[taille_tableau] = {0};

        // On parcours à nouveau le fichier pour remplir les tableaux avec la durée des 1 et des 0
        f.seekg(40);

        var = 1;
        boucle = true;

        int c = 0; //Compteur du nombre de sample

        //Variables qui stockent la durée maximale et minimale d'un son et d'un silence
        int min0 = taille;
        int min1 = taille;
        int max0 = 0;
        int max1 = 0;

        for (int i = 0; f.tellg() < taille ; i++)
        {
            // Lecture d'un son
            for (; f.tellg() < taille and boucle ;)
            {
                f.read(reinterpret_cast<char *>(&var), sizeof (var));
                c++;
                if (var == 0 and f.tellg() < taille)
                {
                    f.read(reinterpret_cast<char *>(&var), sizeof (var));
                    c++;
                    if (var == 0)
                    {
                        boucle = false;
                    }
                }
            }

            boucle = true;

            uns[i] = c;

            max1 = max(c, max1);
            min1 = min(c, min1);

            c = 0;

            // Lecture d'un silence
            for (int i = 0; f.tellg() < taille and var == 0 ; i++)
            {
                f.read(reinterpret_cast<char *>(&var), sizeof (var));
                c++;
            }

            zeros[i] = c;

            max0 = max(c, max0);
            min0 = min(c, min0);

            c = 0;
        }

        // On parcours les tableaux pour déterminer les caractères mosrses            
        for(int i = 0; i < taille_tableau ; i++)
        {
            // On est parti du principe que tous les fichiers commencent par un son
            int un = uns[i];
            int zero = zeros[i];

            // On se donne une marge d'erreur de 10%
            if (un < 1.1*max1 and un > 0.9*max1)
            {
                morse += (string)"_";
            }
            else if (un < 1.1*min1 and un > 0.9*min1)
            {
                morse += (string)".";
            }

            if (zero < 1.1*min0 and zero > 0.9*min0){} // C'est juste un espace entre caractère morse
            else if (zero < 1.1*max0 and zero > 0.9*max0)
            {
                morse += (string)" / ";
            }
            else
            {
                morse += (string)" "; // Si ce n'est ni un espace entre caractères morses ni un espace entre mots, c'est un espace entre lettres
            }
        }
        
        f.close();
    }
    morse_texte = morse;
}