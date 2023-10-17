#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Kattis - tritiling

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    while(n != -1){
        if(n % 2 == 1){
            cout << "0\n";
            cin >> n;
            continue;
        }
        vector<ll> col(n + 1, 0);
        col[0] = 1;
        for(int i = 0; i < n; i++){
            col[i + 1] += col[i];
            if(i + 2 <= n){
                col[i + 2] += col[i];
            }
            if(i % 2 == 0){
                //we can swap sides
                col[i + 1] += col[i];
            }
        }
        cout << col[n] << "\n";
        cin >> n;
    }    
    
    return 0;
}
