#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1891B

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- ){
        int n, q;
        cin >> n >> q;
        vector<ll> a(n);
        vector<set<int>> bits(31, set<int>());
        for(int i = 0; i < n; i++){
            cin >> a[i];
            int min_bit = 0;
            ll tmp = a[i];
            while(tmp % 2 == 0){
                min_bit ++;
                tmp /= 2;
            }
            bits[min_bit].insert(i);
        }
        for(int i = 0; i < q; i++){
            int bit;
            cin >> bit;
            for(int j = bit; j < 31; j++){
                for(auto k = bits[j].begin(); k != bits[j].end(); k++){
                    int ind = *k;
                    bits[bit - 1].insert(ind);
                    a[ind] += (1 << (bit - 1));
                }
                bits[j].clear();
            }
        }
        for(int i = 0; i < n; i++){
            cout << a[i] << " \n"[i == n - 1];
        }
    }
    
    return 0;
}
