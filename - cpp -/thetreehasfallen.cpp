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

//Codeforces - 1778E

//nice xor basis problem. 

//let's think about solving the problem if the root is fixed. In this case, if we can generate a xor basis for any
//subtree, then we've solved the problem. 

//generating the xor basis over any subtree seems hard, but can we transfer it to another problem? If we take a 
//preorder traversal of the tree, then we can convert the problem into generating the xor basis over any subarray
//which I know how to do (https://codeforces.com/contest/1100/problem/F). 

//so now let's consider the original problem with the unfixed root. First, arbitrarily root the tree. 
//For queries, there seems like there are 3 cases:
//1. v = r, we just need to get the xor basis for the whole tree
//2. v is ancestor of r, use binary lifting to get node below v that is in direction of r, then compute xor basis for 
//   rest of tree excluding that proper subtree
//3. otherwise, v is proper subtree of our arbitrarily rooted tree. 

const int B = 30;
bool basisInsert(vector<int>& b, int x){
    for(int i = B - 1; i >= 0; i--){
        if((x & (1 << i)) == 0) continue;
        if(!b[i]) {b[i] = x; return true;}
        x ^= b[i];
    }
    return false;
}

bool inBasis(vector<int>& b, int x){
    for(int i = B - 1; i >= 0; i--)
        if(x & (1 << i)) x ^= b[i];
    return x == 0;
}

int basisMax(vector<int>& b) {
    int ans = 0;
    for(int i = B - 1; i >= 0; i--) if(b[i] && !(ans & (1 << i))) ans ^= b[i];
    return ans;
}

const int N = 2e5 + 100;
int a[N], tour[N], lo[N], ro[N], d[N];
vvi c, p;

void gen_tour(int cur, int par, int& tptr) {
    p[cur][0] = par;
    lo[cur] = tptr;
    tour[tptr ++] = a[cur];
    for(int x : c[cur]) if(x != par) d[x] = d[cur] + 1, gen_tour(x, cur, tptr);
    ro[cur] = tptr;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        c = vvi(n);
        for(int i = 0; i < n - 1; i++){
            int u, v;
            cin >> u >> v;
            u --, v --;
            c[u].push_back(v);
            c[v].push_back(u);
        }
        int tptr = 0;
        d[0] = 0;
        p = vvi(n, vi(20));
        gen_tour(0, -1, tptr);
        vvi b(n + 1);
        for(int i = n - 1; i >= 0; i--){
            vi ba(B, 0);
            b[i].push_back(i);
            basisInsert(ba, tour[i]);
            for(int j = 0; j < b[i + 1].size(); j++) if(basisInsert(ba, tour[b[i + 1][j]])) b[i].push_back(b[i + 1][j]);
        }
        for(int i = 1; i < 20; i++){
            for(int j = 0; j < n; j++){
                if(p[j][i - 1] != -1) p[j][i] = p[p[j][i - 1]][i - 1];
            }
        }
        // cout << "D : " << "\n";
        // for(int i = 0; i < n; i++){
        //     cout << d[i] << " ";
        // }
        // cout << "\n";
        int q;
        cin >> q;
        for(int i = 0; i < q; i++){
            int r, v;
            cin >> r >> v;
            r --, v --;
            vi ba(B, 0);
            // cout << "L R : " << lo[v] << " " << ro[v] << " " << lo[r] << " " << ro[r] << "\n";
            if(r == v) {
                for(int j = 0; j < b[0].size(); j++) basisInsert(ba, tour[b[0][j]]);
            }
            else if(!(lo[v] < lo[r] && ro[r] <= ro[v])) {
                // cout << "PROPER SUBTREE\n";
                for(int j = 0; j < b[lo[v]].size(); j++) if(b[lo[v]][j] < ro[v]) basisInsert(ba, tour[b[lo[v]][j]]);
            }
            else {
                // cout << "IMPROPER SUBTREE\n";
                int dist = d[r] - d[v];
                // cout << "D : " << d[r] << " " << d[v] << endl;
                dist --;
                v = r;
                // cout << "DIST : " << dist << endl;
                for(int j = 0; j < 20; j++){
                    // cout << "ITER : " << v << endl;
                    if(dist & (1 << j)) v = p[v][j];
                }
                // cout << "V : " << v << endl;
                for(int j = 0; j < b[0].size(); j++) if(b[0][j] < lo[v]) basisInsert(ba, tour[b[0][j]]);
                for(int j = 0; j < b[ro[v]].size(); j++) basisInsert(ba, tour[b[ro[v]][j]]);
            }
            cout << basisMax(ba) << "\n";
        }
    }
    
    return 0;
}