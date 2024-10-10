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

//Codeforces - 1996G

//some friendship a -> b can have two 'orientations'. Either they can go clockwise or counterclockwise. 
//note that removing any road will uniquely determine the orientations of all friendships. Also note
//that if the resulting orientations from removing one road is different from removing another road,
//then those two roads cannot be removed simultaneously. 

//therefore the solution is to find the set of orientations such that the most amount of roads will
//result in it once we remove it. We can represent an orientation state using a xor hash, and just 
//iterate through all the roads. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    srand(time(0));
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        map<ll, int> scnt;
        vvi c(n);
        vl h(m);
        for(int i = 0; i < m; i++){
            int a, b;
            cin >> a >> b;
            a --;
            b --;
            c[a].push_back(i);
            c[b].push_back(i);
            ll r1 = rand();
            ll r2 = rand();
            ll r3 = rand();
            ll r4 = rand();
            h[i] = r1 + (r2 << 16) + (r3 << 32) + (r4 << 48);
        }
        ll hash = 0;
        for(int i = 0; i < n; i++){
            scnt[hash] ++;
            for(int j = 0; j < c[i].size(); j++){
                int next = c[i][j];
                hash ^= h[next];
            }
        }
        int ans = 0;
        for(auto i = scnt.begin(); i != scnt.end(); i++){
            ans = max(ans, i->second);
        }
        ans = n - ans;
        cout << ans << "\n";
    }
    
    return 0;
}