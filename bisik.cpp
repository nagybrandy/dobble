//k=11
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include "cards.h"

using namespace std;

struct Point
{
    int I;
    int ind;
    Point() {}
    Point(int x, int y) : I(x), ind(y) {}
    bool operator==(const Point& p) const {
        return (p.I == I && p.ind == ind);
    }

    bool operator<(const Point& p) const {
        return ((I < p.I) || ((I == p.I) && (ind < p.ind)));
    }
};

typedef vector<Point> Ciklus;
typedef vector<Ciklus> Aumorf;
array<Aumorf, 3> autos;

typedef array<Point, 11> Base;
vector<Base> bases;
typedef array<Point, 13> Base2;
vector<Base2> bases2;
vector<vector<int>> result;

Base doauto(const Base base, const Aumorf au) {
    Base newbase = base;
    for_each(newbase.begin(), newbase.end(), [au](Point& p) {
        bool found = false;
        size_t i = 0;
        while (!found && i < au.size()) {
            auto it = find(au[i].begin(), au[i].end(), p);
            if (it == au[i].end() - 1) {
                //benne van a vegen
                found = true;
                p = *au[i].begin();
            }
            else if (it != au[i].end()) {
                //benne van nem a vegen
                found = true;
                p = *(it + 1);
            }
            ++i;
        }
        });
    return newbase;
}

Base2 doauto2(const Base2 base, const Aumorf au) {
    Base2 newbase = base;
    for_each(newbase.begin(), newbase.end(), [au](Point& p) {
        bool found = false;
        size_t i = 0;
        while (!found && i < au.size()) {
            auto it = find(au[i].begin(), au[i].end(), p);
            if (it == au[i].end() - 1) {
                //benne van a vegen
                found = true;
                p = *au[i].begin();
            }
            else if (it != au[i].end()) {
                //benne van nem a vegen
                found = true;
                p = *(it + 1);
            }
            ++i;
        }
        });
    return newbase;
}

void k13()
 {
    //A: (11,0); B: (12,0)
    //basek feltoltese
    Base2 base = { Point(11,0), Point(12,0), Point(6,0), Point(6,1), Point(6,2), Point(6,3), Point(6,4), Point(6,5), Point(6,6), Point(6,7), Point(6,8), Point(6,9), Point(6,10) };
    sort(base.begin(), base.end());
    bases2.push_back(base);

    base = { Point(11,0), Point(12,0), Point(7,0), Point(7,1), Point(7,2), Point(7,3), Point(7,4), Point(7,5), Point(7,6), Point(7,7), Point(7,8), Point(7,9), Point(7,10) };
    sort(base.begin(), base.end());
    bases2.push_back(base);

    base = { Point(11,0), Point(1,1), Point(1,4), Point(2,4), Point(2,5), Point(3,5), Point(3,9), Point(4,9), Point(4,3), Point(5,3), Point(5,1), Point(6,0), Point(7,0) };
    sort(base.begin(), base.end());
    bases2.push_back(base);
    
    base = { Point(12,0), Point(1,10), Point(1,7), Point(2,7), Point(2,6), Point(3,6), Point(3,2), Point(4,2), Point(4,8), Point(5,8), Point(5,10), Point(6,0), Point(7,0) };
    sort(base.begin(), base.end());
    bases2.push_back(base);

    base = { Point(1,0), Point(2,2), Point(2,9), Point(2,4), Point(2,7), Point(3,5), Point(3,6), Point(5,4), Point(5,7), Point(6,2), Point(6,9), Point(7,5), Point(7,6) };
    sort(base.begin(), base.end());
    bases2.push_back(base);

    auto itautos = autos.begin();
    //1.fajta
    Aumorf au;
    for (int i = 1;i < 8;i++) {
        au.push_back({ Point(i, 0), Point(i, 1), Point(i, 2), Point(i, 3), Point(i, 4), Point(i, 5), Point(i, 6), Point(i, 7), Point(i, 8), Point(i, 9), Point(i, 10) });
    }
    *itautos = au;
    ++itautos;

    //2.fajta
    au.clear();
    for (int i = 0;i < 11;i++) {
        au.push_back({ Point(1, i), Point(2, i * 4 % 11), Point(3, i * 5 % 11), Point(4, i * 9 % 11), Point(5, i * 3 % 11) });
        au.push_back({ Point(6, i), Point(6, i * 4 % 11), Point(6, i * 5 % 11), Point(6, i * 9 % 11), Point(6, i * 3 % 11) });
        au.push_back({ Point(7, i), Point(7, i * 4 % 11), Point(7, i * 5 % 11), Point(7, i * 9 % 11), Point(7, i * 3 % 11) });
    }
    *itautos = au;
    ++itautos;
    //3.fajta
    au.clear();
    for (int i = 0;i < 11;i++) {
        au.push_back({ Point(11, 0), Point(12,0) });
        for (int j = 1;j < 8;j++) {
            au.push_back({ Point(j, i), Point(j, i * 10 % 11) });
        }
    }
    *itautos = au;
    ++itautos;
    //auto alkalmazasa
    size_t i = 0;
    while (i < bases2.size()) {
        for_each(autos.begin(), autos.end(), [i](Aumorf& au) {
            Base2 newbase = doauto2(bases2[i], au);
            //alkalmaztam, uj-e
            sort(newbase.begin(), newbase.end());
            if (find(bases2.begin(), bases2.end(), newbase) == bases2.end()) {
                //nem tartalmazza, uj
                bases2.push_back(newbase);
            }
            });
        ++i;
    }
    for (int i = 0;i < bases2.size();i++) {
        vector<int> resbase;
        for (int j = 0;j < 13;j++) {
            if (bases2[i][j].I == 11) {
                resbase.push_back(77);
            }
            else if (bases2[i][j].I == 12) {
                resbase.push_back(78);
            }
            else {
                resbase.push_back(bases2[i][j].ind * 7 + bases2[i][j].I - 1);
            }
        }
        result.push_back(resbase);
    }
}

void k11() {
    //basek feltoltese
    Base base = { Point(1,1), Point(2,2), Point(3,4), Point(4,1), Point(5,2), Point(6,4), Point(7,0), Point(7,3), Point(7,6), Point(7,5), Point(8,0) };
    sort(base.begin(), base.end());
    bases.push_back(base);

    base = { Point(1,2), Point(1,5), Point(2,2), Point(2,5), Point(3,1), Point(3,6), Point(4,0), Point(4,1), Point(4,6), Point(7,1), Point(8,6) };
    sort(base.begin(), base.end());
    bases.push_back(base);

    auto itautos = autos.begin();
    //1.fajta
    Aumorf au;
    for (int i = 1;i < 9;i++) {
        au.push_back({ Point(i, 0), Point(i, 1), Point(i, 2), Point(i, 3), Point(i, 4), Point(i, 5), Point(i, 6) });
    }
    *itautos = au;
    ++itautos;

    //2.fajta
    au.clear();
    for (int i = 0;i < 7;i++) {
        au.push_back({ Point(1, i), Point(2, i * 2 % 7), Point(3, i * 4 % 7) });
        au.push_back({ Point(4, i), Point(5, i * 2 % 7), Point(6, i * 4 % 7) });
        au.push_back({ Point(7, i), Point(7, i * 2 % 7), Point(7, i * 4 % 7) });
        au.push_back({ Point(8, i), Point(8, i * 2 % 7), Point(8, i * 4 % 7) });

    }
    *itautos = au;
    ++itautos;
    //3.fajta
    au.clear();
    for (int i = 0;i < 7;i++) {
        au.push_back({ Point(1, i), Point(4, i * 6 % 7) });
        au.push_back({ Point(2, i), Point(5, i * 6 % 7) });
        au.push_back({ Point(3, i), Point(6, i * 6 % 7) });
        au.push_back({ Point(7, i), Point(8, i * 6 % 7) });
    }
    *itautos = au;
    ++itautos;
    //auto alkalmazasa
    size_t i = 0;
    while (i < bases.size()) {
        for_each(autos.begin(), autos.end(), [i](Aumorf& au) {
            Base newbase = doauto(bases[i], au);
            //alkalmaztam, uj-e
            sort(newbase.begin(), newbase.end());
            if (find(bases.begin(), bases.end(), newbase) == bases.end()) {
                //nem tartalmazza, uj
                bases.push_back(newbase);
            }
            });
        ++i;
    }
    for (int i = 0;i < bases.size();i++) {
        vector<int> resbase;
        for (int j = 0;j < 11;j++) {
            resbase.push_back(bases[i][j].ind * 8 + bases[i][j].I - 1);
        }
        result.push_back(resbase);
    }
    for (int i = 0;i < result.size();i++) {
        for (int j = 0;j < 11;j++) {
            cout << result[i][j]  << ' ';
        }
        cout << endl;
    }
}

void k9() {
    for (int i = 0;i < 37;i++) {
        vector<int> base2;
        base2.push_back(i); base2.push_back((i + 6) % 37); base2.push_back((i + 8) % 37);
        base2.push_back((i + 9) % 37); base2.push_back((i + 11) % 37); base2.push_back((i + 15) % 37);
        base2.push_back((i + 25) % 37); base2.push_back((i + 32) % 37); base2.push_back((i + 33) % 37);
        result.push_back(base2);
    }
}

vector<vector<int>> bisik(int k)
{
    //int k;
    //cin >> k;
    if (k == 13) {
        k13();
    }
    else if (k == 11) {
        k11();
    }
    else {
        k9();
    }

    return result;
    

    /*cout << autos.size();
    for (int i = 0;i < bases.size();i++) {
        for (int j = 0;j < 11;j++) {
            cout << bases[i][j].I << bases[i][j].ind << ' ';
        }
        cout << endl;
    }*/
}
