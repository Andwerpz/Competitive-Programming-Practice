
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 29A

using namespace std;

int main() {

    int n;
    cin >> n;
    vector<int> spots(30000);
    for(int i = 0; i < n; i++){
        int x, d;
        cin >> x >> d;
        x += 15000;
        spots[x] = d;
    }
    bool isValid = false;
    for(int i = 0; i < spots.size(); i++){
        if(spots[i] != 0){
            int diff = spots[i];
            int next = i + diff;
            if(next >= 0 && next < spots.size() && spots[next] == -diff){
                isValid = true;
                break;
            }
        }
    }
    cout << (isValid? "YES\n" : "NO\n");

    return 0;
}



