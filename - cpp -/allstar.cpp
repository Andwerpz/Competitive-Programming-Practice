#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

//The 3rd Universal Cup. Stage 18: Southeastern Europe - A

//you can try every single node and take the best one. 

//observe that the number of operations for a node i is equal to (n - 1) - deg(i). Using the operations correctly, we can
//move every edge to the correct position in exactly one operation. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n;
    cin >> n;
    vector<vi> c(n);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --, v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    int bans = 1e9;
    int ians = -1;
    for(int i = 0; i < n; i++){
        int cans = n - c[i].size();
        if(cans < bans) bans = cans, ians = i;
    }
    vector<bool> v(n, false);
    v[ians] = true;
    queue<int> q;
    vector<vi> ans;
    for(int x : c[ians]) q.push(x), v[x] = true;
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        for(int x : c[cur]) {
            if(v[x]) continue;
            v[x] = true;
            q.push(x);
            ans.push_back({ians, cur, x});
        }
    }
    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i][0] + 1 << " " << ans[i][1] + 1 << " " << ans[i][2] + 1 << "\n";
    }

    return 0;
}