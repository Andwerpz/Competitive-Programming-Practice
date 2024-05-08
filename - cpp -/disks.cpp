#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __ll128 lll;
// typedef __float128 lld;
using namespace std;

//2024 ICPC EUC - I

//if we increase the radius of a disk, then any disk that is tangent to it must decrease their radii by an equal
//amount. 

//therefore it's natural to construct a graph out of tangent disks. You'll notice that if a connected component is 
//2 colorable, then expanding the radius of a disk of one color will make all other disks of the same color
//expand, and all disks of the opposite color will shrink. 

//So, we just have to find if there is a 2 colorable component such that the number of one color is not equal to the 
//number of disks of the other color. 

//note that if a component is not 2 colorable, then it's impossible to change the size of any disk in that component. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n;
    cin >> n;
    vector<pair<ll, pair<ll, ll>>> a(n);
    for(ll i = 0; i < n; i++){
        cin >> a[i].second.first >> a[i].second.second >> a[i].first;
    }
    vector<vector<ll>> c(n);
    for(ll i = 0; i < n; i++){
        for(ll j = i + 1; j < n; j++){
            ll x0 = a[i].second.first;
            ll y0 = a[i].second.second;
            ll r0 = a[i].first;
            ll x1 = a[j].second.first;
            ll y1 = a[j].second.second;
            ll r1 = a[j].first;
            ll dx = x0 - x1;
            ll dy = y0 - y1;
            if((r0 + r1) * (r0 + r1) == dx * dx + dy * dy) {
                c[i].push_back(j);
                c[j].push_back(i);
            }
        }
    }
    bool is_valid = false;
    vector<bool> v(n, false);
    vector<ll> color(n, -1);
    for(ll i = 0; i < n; i++){
        if(v[i]) {
            continue;
        }
        queue<ll> q;
        q.push(i);
        v[i] = true;
        color[i] = 0;
        ll zcnt = 0;
        ll ocnt = 0;
        bool color_valid = true;
        while(q.size() != 0){
            ll cur = q.front();
            q.pop();
            if(color[cur] == 0) {
                zcnt ++;
            }
            else {
                ocnt ++;
            }
            for(ll j = 0; j < c[cur].size(); j++){
                ll next = c[cur][j];
                ll ncolor = color[cur] ^ 1;
                if(color[next] != -1 && color[next] != ncolor) {
                    color_valid = false;
                }
                if(!v[next]) {
                    v[next] = true;
                    color[next] = ncolor;
                    q.push(next);
                }
            }
        }
        if(zcnt != ocnt && color_valid){
            is_valid = true;
        }
    }
    cout << (is_valid? "YES" : "NO") << "\n";
    
    return 0;
}
