#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <fstream>
#include "cards.h"

using namespace std;

int tipus; //0: projektiv, 1: bisik
//kartyak es szimbolumok szama egy kartyan (q+1)
int k; //bisik: {9,11,13}; proj:{2,3,4,5,6,7,8,9,10,12,...}
int n; //szimbolumok szama
const int maxn = 1000;
int szimtip; //0:kepek, 1:szoveg
int megjelenes; //0:egyforma, 1:kulonbozo

vector<vector<int>> cardsresult;

int main() {
    cout << "Jatek tipusa (0: projektiv, 1: bisik): ";
    cin >> tipus;
    cout << "Szimbolumok szama egy kartyan: ";
    cin >> k;
    cout << "Szimbolumok tipusa (0: kepek, 1: szoveg): ";
    cin >> szimtip;
    cout << "Szimbolumok megjelenese (0:egyforma, 1:kulonbozo): ";
    cin >> megjelenes;

    if (tipus == 0) {
        //proj
        n = (k - 1) *(k-1) + k;
        cardsresult = proj(k);
    }
    else {
        //bisik
        n = (k * (k - 1)) / 2 + 1;
        cardsresult = bisik(k);
    }

    vector<vector<Keptipus> > pics;

    if (megjelenes == 1) {
        //kul megjelenes
        cout << "Tolts fel " << n << " db kepet," << k << "megjelenessel!" << endl;
        Keptipus picname;
        for (int i = 0;i < n;i++) {
            int ossz = 0;
            vector<Keptipus> s;
            while (ossz < k) {
                cin >> picname.nev;
                cin >> picname.ismetlodes;
                ossz += picname.ismetlodes;
                s.push_back(picname);
            }
            pics.push_back(s);
        }
    }
    else {
        cout << "Tolts fel " << n << " db kepet!" << endl;
        Keptipus picname;
        for (int i = 0;i < n;i++) {
            vector<Keptipus> s;
            cin >> picname.nev;
            picname.ismetlodes = 1;
            s.push_back(picname);
            pics.push_back(s);
        }
    }

    getlatex(pics, cardsresult, n, k, szimtip);

    for (vector<int> base : cardsresult) {
        for (int point : base) {
            cout << point << ' ';
        }
        cout << endl;
    }

    return 0;
}

