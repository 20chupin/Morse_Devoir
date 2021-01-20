#include <iostream>
#include <fstream>
#include <cmath>

#include "../include/audio.h"

using namespace std;

audio::audio(){}
    
audio::~audio(){}

namespace little_endian_io
{
  template <typename Word>
  std::ostream& write_word( std::ostream& outs, Word value, unsigned size = sizeof( Word ) )
  {
    for (; size; --size, value >>= 8)
      outs.put( static_cast <char> (value & 0xFF) );
    return outs;
  }
}
using namespace little_endian_io;

void audio::m_to_s(string mrs)
{
    ofstream f("traduction.wav", ios::binary ); //crée et ouvre le fichier en binaire

    // En-tête
    f << "RIFF----WAVEfmt ";     // La taille sera remplie après
    write_word( f,     16, 4 );
    write_word( f,      1, 2 );
    write_word( f,      2, 2 );
    write_word( f,  44100, 4 );  // fréquence d'échantillonage (Hz)
    write_word( f, 176400, 4 );
    write_word( f,      4, 2 );
    write_word( f,     16, 2 );
    
    // Repérage de la position
    size_t pos = f.tellp();
    f << "data----";

    // Traduction du message en morse texte en audio

    int N = hz * seconds;  //A CHANGER

    bool son = 1;
    float imp = ti;
    int c = 0; // Numéro de la période d'échantillonage

    for (int n = 0; mrs[n] != 0; n++)
    {
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
            imp = 5*ti;
        }

        // Son correspondant à l'information
        for (int i = 0; i < hz * imp ; i++)
        {
            double amplitude = (double)c / N * max_amplitude;
            double value     = sin( (two_pi * c * frequency) / hz ) * son;
            write_word( f, (int)(                 amplitude  * value), 2 );
            write_word( f, (int)((max_amplitude - amplitude) * value), 2 );
            c+=1;
        }

        // Un ti de silence (dans tous les cas)
        for (int i = 0; i < hz * ti ; i++){
            write_word( f, 0, 2 );
            write_word( f, 0, 2 );
            c+=1;
        }
    }
    
    // Taille finale du fichier
    size_t file_length = f.tellp();

    // Ecrire la taille finale des données
    f.seekp(pos + 4);
    write_word(f, file_length - pos + 8 );

    // Ecrire la taille totale - 8 dans l'en-tête
    f.seekp(4);
    write_word( f, file_length - 8, 4 );
}

void audio::s_to_m(string file_name)
{
    string morse="";
    ifstream f(file_name, ios::binary);
    if (f.is_open())
    {
        f.ignore(40);
        uint32_t taille;
        f.read(reinterpret_cast<char *>(&taille), sizeof (taille));

        // Obtenir la taille du tableau qui va stocker la durée des 1 et des 0
        int taille_tableau = 0;
        uint32_t var = 1;
        bool boucle = true;
        for (; f.tellg() < taille ;)
        {
            taille_tableau++;
            for (; f.tellg() < taille and boucle ;)
            {
                f.read(reinterpret_cast<char *>(&var), sizeof (var));
                if (var == 0 and f.tellg() < taille)
                {
                    f.read(reinterpret_cast<char *>(&var), sizeof (var));
                    if (var == 0)
                    {
                        boucle = false;
                    }
                }
            }
            boucle = true;
            for (; f.tellg() < taille and var == 0 ;)
            {
                f.read(reinterpret_cast<char *>(&var), sizeof (var));
            }
        }
        int uns[taille_tableau] = {0};
        int zeros[taille_tableau] = {0};

        // Remplir les tableaux avec la durée des 1 et des 0
        f.seekg(40);
        var = 1;
        boucle = true;

        int c = 0;
        int min0 = taille;
        int min1 = taille;
        int max0 = 0;
        int max1 = 0;
        for (int i = 0; f.tellg() < taille ; i++)
        {
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

        // Analyser le caractère morse            
        for(int i = 0; i < taille_tableau ; i++)
        {
            int un = uns[i];
            int zero = zeros[i];
            if (un < 1.1*max1 and un > 0.9*max1)
            {
                morse += (string)"_";
            }
            else if (un < 1.1*min1 and un > 0.9*min1)
            {
                morse += (string)".";
            }
            if (zero < 1.1*min0 and zero > 0.9*min0){}
            else if (zero < 1.1*max0 and zero > 0.9*max0)
            {
                morse += (string)"/";
            }
            else
            {
                morse += (string)" ";
            }
        }
    }
    cout<<morse;
}