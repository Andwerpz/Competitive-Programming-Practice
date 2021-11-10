
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1334A

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        bool isValid = true;
        int prevAttempts = 0;
        int prevClears = 0;
        for(int i = 0; i < n; i++){
            int curAttempts = 0;
            int curClears = 0;
            cin >> curAttempts >> curClears;
            int da = curAttempts - prevAttempts;
            int dc = curClears - prevClears;
            if(dc > da || dc < 0 || da < 0){
                isValid = false;
            }
            prevAttempts = curAttempts;
            prevClears = curClears;
        }
        cout << (isValid? "YES\n" : "NO\n");
    }

    return 0;
}
