#pragma once

#include <iostream>
#include <map>

using namespace std;

// Cette classe sert à la traduction du texte de morse écrit vers français écrit ou de français écrit vers morse écrit.

class texte
{
public:
    texte(char M_or_F, string txt); // Le constructeur prend en argument la langue (M_or_F pour Morse ou Français) et le texte à traduire (txt)
    ~texte();

public:
    string morse_getter();
    string francais_getter();

public:
    void encode(); // Français vers morse
    void decode(); // Morse vers Français

private:
// Comme il n'y a pas de setter, un unique mot correspond à la création d'une instance texte, soit un mot en morse, soit un mot en français
    string morse = "";
    string francais = "";

// Dictionnaire français vers morse
    map<char , string> fr_to_m = {
    {'A',"._"},
    {'B',"_..."},
    {'C',"_._."},
    {'D',"_.."},
    {'E',"."},
    {'F',".._."},
    {'G',"__."},
    {'H',"...."},
    {'I',".."},
    {'J',".___"},
    {'K',"_._"},
    {'L',"._.."},
    {'M',"__"},
    {'N',"_."},
    {'O',"___"},
    {'P',".__."},
    {'Q',"__._"},
    {'R',"._."},
    {'S',"..."},
    {'T',"_"},
    {'U',".._"},
    {'V',"..._"},
    {'W',".__"},
    {'X',"_.._"},
    {'Y',"_.__"},
    {'Z',"__.."},
    {'1',".____"},
    {'2',"..___"},
    {'3',"...__"},
    {'4',"...._"},
    {'5',"....."},
    {'6',"_...."},
    {'7',"__..."},
    {'8',"___.."},
    {'9',"____."},
    {'0',"_____"},
    {' ',"/"},
    {'.',"._._._"},
    {',',"__..__"},
    {'?',"..__.."}
    };

// Dictionnaire morse vers français
    map<string, char> m_to_fr = {
    {"._",'A'},
    {"_...",'B'},
    {"_._.",'C'},
    {"_..",'D'},
    {".",'E'},
    {".._.",'F'},
    {"__.",'G'},
    {"....",'H'},
    {"..",'I'},
    {".___",'J'},
    {"_._",'K'},
    {"._..",'L'},
    {"__",'M'},
    {"_.",'N'},
    {"___",'O'},
    {".__.",'P'},
    {"__._",'Q'},
    {"._.",'R'},
    {"...",'S'},
    {"_",'T'},
    {".._",'U'},
    {"..._",'V'},
    {".__",'W'},
    {"_.._",'X'},
    {"_.__",'Y'},
    {"__..",'Z'},
    {".____",'1'},
    {"..___",'2'},
    {"...__",'3'},
    {"...._",'4'},
    {".....",'5'},
    {"_....",'6'},
    {"__...",'7'},
    {"___..",'8'},
    {"____.",'9'},
    {"_____",'0'},
    {"/",' '},
    {"._._._",'.'},
    {"__..__",','},
    {"..__..",'?'}
    };
};