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

//Codeforces - 2006A

//note that the difference between the number of '10' and '01' is solely determined by the first and last 
//character. If they are same, the difference is 0, if they are different, abs(difference) = 1. 

//So in the case where the root is already decided, we just need to decide the leaves. 

//If the root is not decided, then we might want to spend a turn deciding that. There's some casework here,
//but not terribly interesting. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vvi c(n);
        for(int i = 0; i < n - 1; i++){
            int u, v;
            cin >> u >> v;
            u --;
            v --;
            c[u].push_back(v);
            c[v].push_back(u);
        }
        string a;
        cin >> a;
        int zc = 0, oc = 0, qc = 0, sc = 0;
        for(int i = 1; i < n; i++){
            if(c[i].size() == 1){
                zc += a[i] == '0';
                oc += a[i] == '1';
                qc += a[i] == '?';
            }
            else if(a[i] == '?') {
                sc ++;
            }
        }
        bool iris_turn = true;
        if(a[0] == '?') {
            bool forced = false;
            forced = forced || zc != oc || sc % 2 == 0;
            if(forced) {
                a[0] = zc > oc? '1' : '0';
                iris_turn = false;
            }
            else {
                a[0] = zc > oc? '0' : '1';
            }
        }
        // cout << zc << " " << oc << " " << qc << "\n";
        while(qc != 0){
            if(iris_turn) {
                zc += a[0] == '1';
                oc += a[0] == '0';
            }
            else {
                zc += a[0] == '0';
                oc += a[0] == '1';
            }
            iris_turn = !iris_turn;
            qc --;
        }
        cout << (a[0] == '0'? oc : zc) << "\n";
    }
    
    return 0;
}