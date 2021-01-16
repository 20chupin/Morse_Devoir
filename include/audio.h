#pragma once

#include <iostream>

using namespace std;

class audio
{
public:
    audio();
    ~audio();

public:
    void m_to_s(string mrs);
    void s_to_m();

public:
    float ti = 0.25;
    float taah = 3*0.25;
    double hz        = 44100;    // samples per second
    double frequency = 880;  // La 440
    double seconds   = 500;      // time
    double two_pi = 6.283185307179586476925286766559;
    double max_amplitude = 32760;  // "volume"
};