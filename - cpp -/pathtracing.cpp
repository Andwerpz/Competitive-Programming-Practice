#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 01 E

//implementation stuff

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n = 1001;
    vector<vector<bool>> v(n, vector<bool>(n, false));
    int startR = 500;
    int startC = 500;
    int curR = 500;
    int curC = 500;
    int minR = 500;
    int maxR = 500;
    int minC = 500;
    int maxC = 500;
    v[curR][curC] = true;
    string s;
    while(getline(cin, s)) {
        if(s.size() == 0){
            break;
        }
        if(s == "down") {
            curR ++;
        }
        if(s == "up") {
            curR --;
        }
        if(s == "right") {
            curC ++;
        }
        if(s == "left") {
            curC --;
        }
        v[curR][curC] = true;
        minR = min(minR, curR);
        maxR = max(maxR, curR);
        minC = min(minC, curC);
        maxC = max(maxC, curC);
    }
    for(int i = minR - 1; i <= maxR + 1; i++) {
        for(int j = minC - 1; j <= maxC + 1; j++) {
            if(i < minR || i > maxR || j < minC || j > maxC) {
                cout << "#";
                continue;
            }
            if(i == startR && j == startC) {
                cout << "S";
                continue;
            }
            if(i == curR && j == curC) {
                cout << "E";
                continue;
            }
            if(v[i][j]) {
                cout << "*";
            }
            else {
                cout << " ";
            }
        }
        cout << "\n";
    }
    
    return 0;
}
