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

void audio::s_to_m(){}