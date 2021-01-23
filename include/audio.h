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
    string morse_texte_getter();

public:
    void m_to_s(string mrs);
    void s_to_m(string file_name);
    void header(string file_name);

private:
    float ti = 0.25;
    float taah = 3*0.25; // Un taah = 3 * ti

    string morse_texte = "";
};