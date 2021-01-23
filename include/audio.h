#pragma once

#include <iostream>
#include <fstream>

using namespace std;

class audio
{
public:
    audio();
    ~audio();

public:
    void m_to_s(string mrs);
    void s_to_m(string file_name);

public:
    float ti = 0.25;
    float taah = 3*0.25;
    


    ofstream f;

    string morse_texte = "";
};