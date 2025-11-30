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

//Codeforces - 2134D

//as with all tree problems, try rooting it first. 
//one slight nuance here, it's ideal to root the tree here on a diameter endpoint. The reason is that
//the optimal amount of moves is equal to (n - 1) - d, where d is the number of edges in the diameter. 

//Then, the optimal first move is to find a junction, then slide all the children down one of the edges
//that is not a diameter edge. 

int find_farthest(vvi& c, int n, int s, int& outd, vi& outp) {
    vb v(n, false);
    v[s] = true;
    vi d(n, 1e9), prev(n, -1);
    d[s] = 0;
    queue<int> q;
    q.push(s);
    int ans = -1, ansd = -1;
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        if(d[cur] > ansd) {
            ansd = d[cur];
            ans = cur;
        }
        for(int x : c[cur]){
            if(!v[x]) {
                v[x] = true;
                d[x] = d[cur] + 1;
                prev[x] = cur;
                q.push(x);
            }
        }
    }
    outd = ansd;
    vi p(0);
    int ptr = ans;
    while(ptr != s) {
        p.push_back(ptr);
        ptr = prev[ptr];
    }
    p.push_back(s);
    reverse(p.begin(), p.end());
    outp = p;
    return ans;
}

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
            u --, v --;
            c[u].push_back(v);
            c[v].push_back(u);
        }
        //find diameter endpoints
        int dlen = -1;
        vi p;
        int da = find_farthest(c, n, 0, dlen, p);
        int db = find_farthest(c, n, da, dlen, p);
        //check if it's already a path
        if(dlen == n - 1) {
            cout << "-1\n";
            continue;
        }
        //find first junction
        bool found = false;
        assert(c[p[0]].size() == 1);
        for(int i = 1; i < p.size() - 1; i++){
            if(c[p[i]].size() == 2) continue;
            int pa = p[i - 1], pb = p[i], pc = p[i + 1];
            int opc = -1;
            for(int x : c[p[i]]) {
                if(x != pc && x != pa) {
                    opc = x;
                    break;
                }
            }
            assert(opc != -1);
            pc = opc;
            cout << (pa + 1) << " " << (pb + 1) << " " << (pc + 1) << "\n";
            found = true;
            break;
        }
        assert(found);
    }
    
    return 0;
}