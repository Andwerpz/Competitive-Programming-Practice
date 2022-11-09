#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Kattis anti11hard

//my thought was to use dp to solve. 

//the problem is my solution is counting invalid bitstrings as valid. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll mod = 1e9 + 7;
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        string b;
        cin >> b;
        if(b.size() == 1){
            cout << "1\n";
            continue;
        }
        vector<ll> zdp(n);
        vector<ll> odp(n);
        zdp[0] = 1;
        odp[0] = 1;
        for(int i = 1; i < n; i++){
            ll add = (zdp[i - 1] + odp[i - 1]) % mod;
            if(i < b.size() - 1) {
                zdp[i] = add;
                odp[i] = add;
                continue;
            }
            if(b[b.size() - 1] == '0') {
                odp[i] = add;
                for(int j = 1; j < b.size(); j++){
                    if(b[b.size() - j - 1] == '0'){
                        zdp[i] += odp[i - j];
                    }
                    else{
                        zdp[i] += zdp[i - j];
                    }
                    zdp[i] %= mod;
                }
                //zdp[i] += zdp[i - b.size()] + odp[i - b.size()];
            }
            else {
                zdp[i] = add;
                for(int j = 1; j < b.size(); j++){
                    if(b[b.size() - j - 1] == '0'){
                        odp[i] += odp[i - j];
                    }
                    else{
                        odp[i] += zdp[i - j];
                    }
                    odp[i] %= mod;
                }
                //odp[i] += zdp[i - b.size()] + odp[i - b.size()];
            }
        }
        for(int i : zdp) {
            cout << i << " ";
        }
        cout << "\n";
        for(int i : odp){
            cout << i << " ";
        }
        cout << "\n";
        cout << (zdp[n - 1] + odp[n - 1]) % mod << "\n";
    }
    
    return 0;
}
