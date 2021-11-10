
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1031A

//implementation math

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int w, h, k;
    cin >> w >> h >> k;
    int ans = 0;
    for(int i = 0; i < k; i++){
        if(w == 1){
            ans += h;
        }
        else if(h == 1){
            ans += w;
        }
        else{
            ans += w * 2;
            ans += (h - 2) * 2;
        }
        w -= 4;
        h -= 4;
    }
    cout << ans << endl;

    return 0;
}



