#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1566A

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int n, s;
        cin >> n >> s;
        int positions = n - (n / 2 + (n % 2 == 1? 1 : 0)) + 1;
        //cout << positions << endl;
        cout << (s / positions) << endl;
    }

    return 0;
}



