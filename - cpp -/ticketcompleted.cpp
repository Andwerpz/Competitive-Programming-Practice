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

//RMRC 2021 - L

//divide the amount of 'good' pairs by the total amount of pairs. 

//a good pair needs to be two nodes in the same connected component. Can just directly count that. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n, m;
    cin >> n >> m;
    vvi c(n);
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b ;
        a--;
        b --;
        c[a].push_back(b);
        c[b].push_back(a);
    }
    ll cnt = 0;
    vb v(n, false);
    for(int i = 0; i < n; i++){
        if(v[i]){
            continue;
        }
        queue<int> q;
        ll ccnt = 1;
        v[i] = true;
        q.push(i);
        while(q.size() != 0){
            int cur = q.front();
            q.pop();
            for(int j = 0; j < c[cur].size(); j++){
                int next = c[cur][j];
                if(!v[next]){
                    v[next] = true;
                    ccnt ++;
                    q.push(next);
                }
            }
        }
        cnt += ccnt * (ccnt - 1) / 2;
    }
    ld ans = cnt;
    ans /= (ld) (n * (n - 1) / 2);
    cout << fixed << setprecision(10) << ans << "\n";
    
    return 0;
}