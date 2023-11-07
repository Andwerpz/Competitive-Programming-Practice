#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Kattis - alchemy101

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int m;
        cin >> m;
        int xorsum = 0;
        for(int i = 1; i < m; i++){
            xorsum = xorsum ^ i;
        }
        cout << (m - (xorsum != 0)) << "\n";
        for(int i = 1; i <= m; i++){
            if(i == xorsum) {
                continue;
            }
            cout << i << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
