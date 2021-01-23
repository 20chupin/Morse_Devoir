#include <iostream>
#include <fstream>
#include <cmath>

#include "../include/audio.h"

using namespace std;

audio::audio(){}
    
audio::~audio(){}

/*namespace little_endian_io
{
  template <typename Word>
  std::ostream& write_word( std::ostream& outs, Word value, unsigned size = sizeof( Word ) )
  {
    for (; size; --size, value >>= 8)
      outs.put( static_cast <char> (value & 0xFF) );
    return outs;
  }
}
using namespace little_endian_io;*/

void audio::m_to_s(string mrs)
{   
    double two_pi = 6.283185307179586476925286766559;
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
    
    f.open("traduction.wav", ofstream::binary); //crée et ouvre le fichier en binaire
    
    if (f.is_open())
    {
        // En-tête
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
        
        constexpr double amplitude = 32760;

        double fe        = 44100;    // frequence d'echantillonage
        double frequency = 440.0; // la (critère de Shannon vérifié)

        int temps = 10;
        int N = temps * Frequence;

        int c = 0;
        int son = 1;
        float imp = ti;

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
            else if (mrs[n] == ' ')
            {
                son = 0;
                imp = ti;
            }

            for (int i = 0; i < Frequence * imp ; i++)
            {
                double Son = sin((two_pi * c * 440) / Frequence);
                int SON = (int)(Son * amplitude * son);
                f.write(reinterpret_cast<char *>(&SON), 2);
                c++;
            }
            for (int i = 0; i < Frequence * ti ; i++)
            {
                double Son = 0;
                int SON = (int)(Son * amplitude);
                f.write(reinterpret_cast<char *>(&SON), 2);
                c++;
            }
        }

        size_t file_length = f.tellp();

        f.seekp(data_chunk_pos + 4);
        uint8_t un = file_length - data_chunk_pos + 8;
        f.write(reinterpret_cast<char *>(&un), 4 );

        f.seekp(4);
        uint8_t deux = file_length - 8;
        f.write(reinterpret_cast<char *>(&deux), 4 ); 

        f.close();
    }
    /* double two_pi = 6.283185307179586476925286766559;
    const char* FileInfos = "RIFF----WAVEfmt ";
    uint32_t BlocSize = 16;
    uint16_t AudioFormat = 1;
    uint16_t NbrCanaux = 1;
    uint32_t Frequence = 44100;
    uint32_t BytePerSec = 176400;
    uint16_t BytePerBloc = 4;
    uint16_t BitsPerSample = 16;

    const char* Data = "data----";
    
    f.open("traduction.wav", ofstream::binary); //crée et ouvre le fichier en binaire
    
    if (f.is_open())
    {
        // En-tête
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
        
        constexpr double amplitude = 32760;

        double fe        = 44100;    // frequence d'echantillonage
        double frequency = 440.0; // la (critère de Shannon vérifié)

        int temps = 10;
        int N = temps * Frequence;

        int c = 0;
        bool son = 0;
        float imp = ti;

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
            else if (mrs[n] == ' ')
            {
                son = 0;
                imp = ti;
            }
        
            for (int i = 0; i < 110250 ; i++)
            {
                double Son = sin((two_pi * c * 440) / Frequence);
                int SON = (int)(Son * amplitude);
                f.write(reinterpret_cast<char *>(&SON), 2);
                c++;
            }
            for (int i = 0; i < 110250 ; i++)
            {
                double Son = 0;
                int SON = (int)(Son * amplitude);
                f.write(reinterpret_cast<char *>(&SON), 2);
                c++;
            }
        }

        size_t file_length = f.tellp();

        f.seekp(data_chunk_pos + 4);
        uint8_t un = file_length - data_chunk_pos + 8;
        f.write(reinterpret_cast<char *>(&un), 4 );

        f.seekp(4);
        uint8_t deux = file_length - 8;
        f.write(reinterpret_cast<char *>(&deux), 4 ); 

        f.close();*/
    
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
                morse += (string)" / ";
            }
            else
            {
                morse += (string)" ";
            }
        }
    }
    morse_texte = morse;
}