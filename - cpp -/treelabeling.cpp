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

//2025 Damascus University Programming Contest - A

//with any problem that wants you to generate something that is lexicographically minimal, we do some greedy. 
//so ans[0] = 'a'. However, ans[1] might not be 'a', as it might be connected to node 0. 

//so for each node, we'll keep track of what it can't be. The idea is that when we go to visit a node, 
//we'll always pick the minimum character that it can be. 

//this idea has an issue though, we might choose stuff such that when we get to a node, it actually can't
//be anything. This is when the final idea (guess) comes in: when we update the list of things a node can't be
//if it can't be 2 things after the update, we immediately assign it to be the one thing it can be, and keep
//doing this until everything in the graph is either assigned, or has less than 2 things it can't be. 

//this works because the graph is a tree. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vvi c(n);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --, v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    vb v(n, false);
    vector<char> ans(n, 0);
    vector<set<char>> take(n);
    for(int i = 0; i < n; i++) {
        if(v[i]) continue;
        queue<int> q;
        q.push(i);
        v[i] = true;
        while(q.size() != 0){
            int cur = q.front();
            q.pop();
            for(char j = 'a'; j <= 'c'; j++){
                if(!take[cur].count(j)) {
                    ans[cur] = j;
                    break;
                }
            }
            assert(ans[cur] != 0);
            for(int x : c[cur]) {
                take[x].insert(ans[cur]);
                if(take[x].size() == 2 && !v[x]) q.push(x), v[x] = true;
            }
        }
    }
    for(int i = 0; i < n; i++) cout << ans[i];
    cout << "\n";
    
    return 0;
}