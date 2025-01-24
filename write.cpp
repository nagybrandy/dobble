#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <fstream>
#include "cards.h"

using namespace std;
ofstream variables;

void getlatex(vector<vector<Keptipus> >& pics, vector<vector<int>>& cardsresult, int n, int k, int szimtip) {
    variables.open("variables.tex");
    int pages = n / 6 + 1;
    variables << "\\newcommand{\\numberOfPages}{" << pages << "}\n";
    variables << "\\newcommand{\\numberOfPics}{" << k << "}\n";
    variables << "\\newcommand{\\numberOfCards}{" << n << "}\n";
    if (szimtip == 0) {
        variables << "\\newcommand{\\picType}{1}\n";
    }
    else {
        variables << "\\newcommand{\picType}{0}\n";
    }
	variables << "\\newcommand*{\\pics}{";

    for (vector<int> base : cardsresult) {
        for (int point : base) {
            if (pics[point].size() == 1) {
                //0-tol vagy 1tol megy?
                variables << pics[point][0].nev;
            }
            else {
                int i = 0;
                while (pics[point][i].ismetlodes == pics[point][i].aktism) {
                    i++;
                }
                pics[point][i].aktism++;
                variables << pics[point][i].nev;
            }
            if (!(cardsresult[n - 1] == base && cardsresult[n - 1][k - 1] == point)) {
                variables << ',';
            }
        }
    }

	variables << "}\n";
    variables.close();
}