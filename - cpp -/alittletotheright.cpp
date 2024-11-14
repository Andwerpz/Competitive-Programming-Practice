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

//Alberta Collegiate Programming Contest 2024, Open Division - C

//for a given attribute, there is only one sequence (if any) that can make it strictly increasing. 
//just sort each attribute, and count all valid sequences. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, p;
    cin >> n >> p;
    vector<vector<pii>> a(p, vector<pii>(n));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < p; j++){
            cin >> a[j][i].first;
            a[j][i].second = i;
        }
    }
    set<vi> s;
    for(int i = 0; i < p; i++){
        sort(a[i].begin(), a[i].end());
        bool is_valid = true;
        for(int j = 1; j < n; j++){
            if(a[i][j].first == a[i][j - 1].first) {
                is_valid = false;
            }
        }
        if(is_valid){
            vi v(n);
            for(int j = 0; j < n; j++){
                v[j] = a[i][j].second;
            }
            s.insert(v);
        }
    }
    cout << s.size() << "\n";
    
    return 0;
}