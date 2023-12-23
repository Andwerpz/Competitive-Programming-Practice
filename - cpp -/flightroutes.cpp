#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//USACO 2023 December Contest, Gold P1

//O(n^3) with bitset cheese lmao

//we can consider each direct path in some order, and determine if we should include it or not. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<bitset<800>> bits(n, bitset<800>());
    for(int i = 0; i < n - 1; i++){
        string s;
        cin >> s;
        for(int j = 1 + i; j < n; j++){
            bool bit = s[j - (1 + i)] == '1';
            bits[i][j] = bit;
        }
    }
    vector<bitset<800>> w_bits(n, bitset<800>());
    int ans = 0;
    for(int i = n - 1; i >= 0; i--){
        for(int j = 1 + i; j < n; j++){
            if(w_bits[i][j] != bits[i][j]) {
                w_bits[i][j] = !w_bits[i][j];
                w_bits[i] ^= bits[j];
                ans ++;
            }
        }
    }
    cout << ans << "\n";
    
    return 0;
}
