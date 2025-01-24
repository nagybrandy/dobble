#include <iostream>
#include <vector>

using namespace std;

struct coo {
    int x, y, z;
};

vector<vector<int>> presult;

vector<vector<int>> proj(int k) {
    int q = k - 1;
    //cin >> q;
    int s = q * q + q + 1;

    vector<vector<int>> t; //tartalmazas matrix (0,1)
    vector<coo> points;
    vector<coo> lines;
    
    coo first;
    first.z = 1;
    for (int i = 0;i < q;i++) {
        for (int j = 0;j < q;j++) {
            first.x = i;first.y = j;
            points.push_back(first);
            lines.push_back(first);
        }
    }
    coo second;
    second.y = 1;second.z = 0;
    for (int i = 0;i < q;i++) {
        second.x = i;
        points.push_back(second);
        lines.push_back(second);
    }
    coo third;
    third.x = 1;third.y = 0;third.z = 0;
    points.push_back(third);
    lines.push_back(third);

    /*cout << "lines:" << endl;
    for (coo l : lines) {
        cout << '[' << l.x << ':' << l.y << ':' << l.z << ']' << endl;
    }
    cout << endl << "points:" << endl;
    for (coo p : points) {
        cout << '(' << p.x << ':' << p.y << ':' << p.z << ')' << endl;
    }*/

    /*for (coo l : lines) {
        vector<int> row;
        for (coo p : points) {
            if (((l.x * p.x + l.y * p.y + l.z * p.z) % q) == 0) {
                row.push_back(1);
            }
            else {
                row.push_back(0);
            }
        }
        t.push_back(row);
    }*/

    /*cout << endl << "matrix:" << endl;
    for (int i = 0;i < s;i++) {
        for (int j = 0;j < s;j++) {
            cout << t[i][j] << " ";
        }
        cout << endl;
    }*/

    int m;
    if (q == 1) { m = 2; }
    else { m = q; }

    for (int i = 0;i < lines.size();i++) {
        vector<int> row;
        
        for (int j = 0;j < points.size();j++) {
            if (((lines[i].x * points[j].x + lines[i].y * points[j].y + lines[i].z * points[j].z) % m) == 0) {
                row.push_back(j);
            }
        }
        presult.push_back(row);
    }

    return presult;
}
