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

//3rd Universal Cup, Stage 13 Sendai - E

//observe that you can keep track of all the modifications to the sequence so far, and to find the value at some x,
//just iterate backwards through the modifications. 

//what's the most amount of modifications you have to consider? First, if there are a bunch of type 1 modifications
//in a row, you can clump them all together. For some type 2 modification, if x doesn't get captured by it, you 
//can effectively divide x by 2, so that means you'll have to consider at most 30ish type 2 modifications. Since
//there can be at most 1 type 1 modification in a row, you'll have to consider at most 60 modifications per
//print query, which is fast enough. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int q;
    cin >> q;
    ll n = 1;
    vvi m = {{1}};  //doublings will start with a -1
    while(q--){
        int t, x;
        cin >> t >> x;
        if(t == 1){
            if(m.rbegin()->at(0) == -1) m.push_back({});
            m.rbegin()->push_back(x);
            n ++;
        }
        else if(t == 2){
            m.push_back({-1, x});
            n *= 2;
        }
        else {
            // cout << "XN : " << x << " " << n << "\n";
            if(x > n) {
                cout << "-1\n";
            }
            else {
                for(int i = m.size() - 1; i >= 0; i--){
                    if(m[i][0] == -1) {
                        //doubling
                        if(x % 2) {
                            cout << m[i][1] << "\n";
                            break;
                        }
                        x /= 2;
                    }
                    else {
                        //adding
                        if(x <= m[i].size()) {
                            cout << m[i][m[i].size() - x] << "\n";
                            break;
                        }
                        x -= m[i].size();
                    }
                }
            }
        }
        n = min(n, (ll) 1e10);
    }
    
    return 0;
}