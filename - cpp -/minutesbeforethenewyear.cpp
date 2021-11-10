
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1283A

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int h, m;
        cin >> h >> m;
        int ans = 0;
        if(m != 0){
            ans += 60 - m;
            h ++;
        }
        if(h != 0){
            ans += (24 - h) * 60;
        }
        cout << ans << endl;
    }

    return 0;
}



