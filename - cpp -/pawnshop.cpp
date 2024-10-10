#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
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

//RMRC 2021 - D

//can greedily construct barriers from left to right. Maintain a map storing differences between
//frequencies in a and b. 

void insert(map<int, int>& m, int val) {
    m[val] ++;
    if(m[val] == 0){
        m.erase(val);
    }
}

void erase(map<int, int>& m, int val) {
    m[val] --;
    if(m[val] == 0){
        m.erase(val);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vi a(n), b(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < n; i++){
        cin >> b[i];
    }
    map<int, int> m;
    int ans = 0;
    for(int i = 0; i < n; i++){
        insert(m, a[i]);
        erase(m, b[i]);
        cout << b[i] << " ";
        if(m.size() == 0 && i != n - 1){
            cout << "#" << " ";
        }
        ans += m.size() == 0;
    }
    cout << "\n";
        
    return 0;
}