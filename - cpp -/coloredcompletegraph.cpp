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

//3rd Universal Cup, Stage 13 Sendai - I

//first, we can query all edges of form (1, i). Any edge that is red, we put i into the 'red' set, and all other 
//nodes we put into the 'blue' set. Observe that all nodes in each colored set can visit any other node in their
//respective set, as well as 1. 

//then, the rest of our queries will be between some node in the red set and some node in the blue set. If the edge
//is red, then we can remove the blue node from the blue set, and if the edge is blue, we can remove the 
//red node from the red set. Eventually, one of the sets will become empty, which means that it's possible to 
//create a minimum spanning tree using the other colored edge. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<pii> er, eb;
    set<int> r, b;
    for(int i = 2; i <= n; i++){
        cout << "? 1 " << i << endl;
        string c;
        cin >> c;
        if(c == "R") er.push_back({1, i}), r.insert(i);
        else eb.push_back({1, i}), b.insert(i);
    }
    while(r.size() != 0 && b.size() != 0) {
        int ri = *r.begin(), bi = *b.begin();
        cout << "? " << ri << " " << bi << endl;
        string c;
        cin >> c;
        if(c == "R") er.push_back({ri, bi}), b.erase(bi);
        else eb.push_back({ri, bi}), r.erase(ri);
    }
    vector<pii> ans;
    if(r.size() == 0) ans = eb;
    else ans = er;
    cout << "!\n";
    for(int i = 0; i < n - 1; i++){
        cout << ans[i].first << " " << ans[i].second << "\n";
    }
    cout << endl;
    
    return 0;
}