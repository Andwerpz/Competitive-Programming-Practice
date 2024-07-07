#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

int calc_mex(vector<int> a) {
    sort(a.begin(), a.end());
    if(a[0] != 0){
        return 0;
    }
    for(int i = 1; i < a.size(); i++){
        if(a[i] - 1 > a[i - 1]) {
            return a[i - 1] + 1;
        }
    }
    return a[a.size() - 1] + 1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int e;
    cin >> e;
    vector<int> g(e + 1);
    g[e] = 0;
    for(int i = e - 1; i >= 0; i--){
        vector<int> a(0);
        a.push_back(g[i + 1]);
        if(i * 2 <= e){
            a.push_back(g[i * 2]);
        }
        g[i] = calc_mex(a);
    }
    for(int i = 0; i <= e; i++){
        cout << "I : " << i << ", " << g[i] << "\n";
    }
    
    return 0;
}