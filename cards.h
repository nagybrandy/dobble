#pragma once
#ifndef CARDS_H_INCLUDED
#define CARDS_H_INCLUDED

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

struct Keptipus
{
    string nev; //bemenet
    int ismetlodes; //bemenet
    int aktism = 0;
};

vector<vector<int>> bisik(int k);
vector<vector<int>> proj(int k);
vector<vector<int>> field();
void getlatex(vector<vector<Keptipus> >& pics, vector<vector<int>>& cardsresult, int n, int k, int szimtip);

#endif