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

//Codeforces - 1623E

//at first, seems like a relatively simple greedy problem, but ends up becoming binary lifting 
//implementation practice. 

//how do we solve the problem ignoring time complexity? First, generate the in order traversal, then go left
//to right and consider each character. If the current character is followed by a greater character, then we always
//want to try to duplicate the current one, to delay the appearance of the later one. However, if duplicating the current
//one requires duplicating some character before the current one, then we shouldn't, as it will always make the 
//string greater. (and of course if we ran out of duplicates, we can't dupe the current one). 

//So to summarize, look through each character in order, if the current one precedes a greater character, then try to
//see if we can duplicate by traversing from the current character's node up to the nearest duplicated node, or the root. 

//The issue lies in the traversal. We need a quick way to find what's the nearest ancestor that's duplicated. Obviously
//the answer is binary lifting, but remember, we also need to see if along that path there is a node that appears beforehand
//in the inorder traversal. We can also use binary lifting for this: for each increment, just keep track of the minimum
//index that appears along the increment. 

void dfs(int cur, vector<pii>& c, vi& a){
    if(cur == -1) return;
    dfs(c[cur].first, c, a);
    a.push_back(cur);
    dfs(c[cur].second, c, a);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<pii> c(n);
    vvi p(n, vi(20, -1)), mind(n, vi(20));
    for(int i = 0; i < n; i++){
        cin >> c[i].first >> c[i].second;
        c[i].first --, c[i].second --;
        if(c[i].first != -1) p[c[i].first][0] = i;
        if(c[i].second != -1) p[c[i].second][0] = i;
    }
    for(int i = 1; i < 20; i++){
        for(int j = 0; j < n; j++){
            if(p[j][i - 1] != -1) p[j][i] = p[p[j][i - 1]][i - 1];
        }
    }
    vi a, b(n);
    dfs(0, c, a);
    for(int i = 0; i < n; i++) b[a[i]] = i;
    vector<char> nxt(n);
    nxt[n - 1] = 0;
    for(int i = n - 2; i >= 0; i--){
        if(s[a[i]] == s[a[i + 1]]) nxt[i] = nxt[i + 1];
        else nxt[i] = s[a[i + 1]];
    }
    mind[0][0] = -1;
    for(int i = 1; i < n; i++){
        mind[i][0] = b[p[i][0]];
    }
    for(int i = 1; i < 20; i++){
        for(int j = 0; j < n; j++){
            if(p[j][i - 1] != -1) mind[j][i] = min(mind[j][i - 1], mind[p[j][i - 1]][i - 1]);
        }
    }
    vb d(n, false);
    for(int i = 0; i < n - 1; i++){
        if(s[a[i]] >= nxt[i] || d[a[i]]) continue;
        int cost = 1, ptr = a[i], cmind = i;
        for(int j = 19; j >= 0; j--){
            int nptr = p[ptr][j];
            if(nptr == -1) continue;
            if(!d[nptr]) cost += (1 << j), cmind = min(cmind, mind[ptr][j]), ptr = nptr;
        }
        if(cost <= k && cmind == i) {
            ptr = a[i], k -= cost;
            while(ptr != -1 && !d[ptr]) d[ptr] = true, ptr = p[ptr][0];
        }
    }
    for(int i = 0; i < n; i++){
        cout << s[a[i]];
        if(d[a[i]]) cout << s[a[i]];
    }
    cout << "\n";
    
    return 0;
}