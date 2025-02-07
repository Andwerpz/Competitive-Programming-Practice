#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
typedef vector<int> vi;
typedef vector<ll> vl; 
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 1157E

//since we only care about the lexicographic ordering of the array, we can simply greedily construct
//b from front to back. 

//for every element in a, we just want to greedily pick the element in b that minimizes (a[i] + b[i]) % n. 
//this can be done using an ordered set and lower_bound. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    map<int, int> f;
    vi a(n), b(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];
    for(int i = 0; i < n; i++) f[b[i]] ++;
    for(int i = 0; i < n; i++){
        int tgt = (n - a[i]) % n;
        if(f.lower_bound(tgt) != f.end()) {
            int val = f.lower_bound(tgt)->first;
            cout << (a[i] + val) % n << " ";
            f[val] --;
            if(f[val] == 0) f.erase(val);
        }
        else {
            int val = f.lower_bound(0)->first;
            cout << (a[i] + val) % n << " ";
            f[val] --;
            if(f[val] == 0) f.erase(val);
        }
    }
    cout << "\n";
    
    return 0;
}