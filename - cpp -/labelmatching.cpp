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

//2025 ICPC Asia Chengdu Regional Contest - L

//how to solve just one subtree?
//denote sa[i], sb[i], as the amount of 'surplus' labels from a and b respectively in subtree i
//denote wa[i], wb[i], as the amount of wildcards from a and b respectively from subtree i
//observe that if wa[i] >= sb[i] && wb[i] >= sa[i], then it's always possible to rearrange the labels in a
//so that they're all equal. 

//so we just need to compute sa, sb, wa, wb. wa, wb, seem very easy to do. sa, sb, are the problematic ones. 
//the solution I came up with uses small to large merging. For each subtree, keep a map, f[i], such that
//f[i][x] contains number of a labels in i that are x, minus the number of b labels in i that are x. 

//then, sa[i] = sum of positive f[i][x] and sb[i] = sum of negative f[i][x] (absolute value ofc).
//then, small to large merging allows us to maintain f[i] in O(n * log(n)) time. 

vi a, b, wa, wb, sa, sb;
vvi c;
string ans;

map<int, int> dfs2(int cur, int p) {
    map<int, int> f;
    sa[cur] = 0;
    sb[cur] = 0;
    if(a[cur] != b[cur]) {
        if(a[cur] != 0) {
            sa[cur] = 1;
            f[a[cur]] ++;
        }
        if(b[cur] != 0) {
            sb[cur] = 1;
            f[b[cur]] --;
        }
    }
    for(int x : c[cur]) {
        if(x == p) continue;
        map<int, int> nf = dfs2(x, cur);
        if(nf.size() > f.size()) {
            swap(nf, f);
            sa[cur] = sa[x];
            sb[cur] = sb[x];
        }
        for(auto i = nf.begin(); i != nf.end(); i++) {
            int val = i->first;
            int amt = i->second;
            if(f[val] > 0) sa[cur] -= f[val];
            else if(f[val] < 0) sb[cur] += f[val];
            f[val] += amt;
            if(f[val] > 0) sa[cur] += f[val];
            else if(f[val] < 0) sb[cur] -= f[val];
        }
    }
    if(wa[cur] >= sb[cur] && wb[cur] >= sa[cur]) {
        ans[cur] = '1';
    }
    return f;
}

void dfs1(int cur, int p) {
    wa[cur] = a[cur] == 0;
    wb[cur] = b[cur] == 0;
    for(int x : c[cur]) {
        if(x == p) continue;
        dfs1(x, cur);
        wa[cur] += wa[x];
        wb[cur] += wb[x];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        a = vi(n), b = vi(n), wa = vi(n, 0), wb = vi(n, 0);
        sa = vi(n), sb = vi(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        for(int i = 0; i < n; i++) cin >> b[i];
        c = vvi(n);
        for(int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u --, v --;
            c[u].push_back(v);
            c[v].push_back(u);
        }
        dfs1(0, -1);
        ans = string(n, '0');
        dfs2(0, -1);
        cout << ans << "\n";
    }
    
    return 0;
}