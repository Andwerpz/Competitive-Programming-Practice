#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Kattis - antiarithmetic

//for each (i, j) pair, we can try to find a k where i < j < k, and they form an arithmetic sequence. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string n_str;
    cin >> n_str;
    while(n_str != "0") {
        int n = stoi(n_str.substr(0, n_str.size() - 1));
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<bool> sfx(n, false);
        bool is_valid = false;
        for(int i = n - 2; i >= 1; i--){
            sfx[a[i + 1]] = true;
            for(int j = 0; j < i; j++){
                int next = a[i] + (a[i] - a[j]);
                if(next >= 0 && next < n && sfx[next]) {
                    is_valid = true;
                }
            }
        }
        cout << (is_valid? "no" : "yes") << "\n";
        cin >> n_str;
    }
    
    return 0;
}
