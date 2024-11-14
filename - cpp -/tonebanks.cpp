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

//CTU Open 2021 - K

//implementation problem. Actually not too bad. 

vi dr = {-1, 1, 0, 0};
vi dc = {0, 0, -1, 1};
int n, m;
string decode(int sr, int sc, vvb& v, vector<string>& g) {
    vector<pii> adj_unv;
    queue<pii> q;
    q.push({sr, sc});
    v[sr][sc] = true;
    while(q.size() != 0){
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        for(int i = 0; i < 4; i++){
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                continue;
            }
            if(v[nr][nc]){
                continue;
            }
            if(g[nr][nc] != g[sr][sc]){
                adj_unv.push_back({nr, nc});
                continue;
            }
            v[nr][nc] = true;
            q.push({nr, nc});
        }
    }
    sort(adj_unv.begin(), adj_unv.end());
    string ans = "";
    int cchar = -1;
    for(int i = 0; i < adj_unv.size(); i++){
        int r = adj_unv[i].first;
        int c = adj_unv[i].second;
        if(!v[r][c]){
            ans += decode(r, c, v, g);
            cchar ++;
        }
    }
    if(cchar != -1){
        reverse(ans.begin(), ans.end());
        ans.push_back('a' + cchar);
        reverse(ans.begin(), ans.end());
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> n >> m;
    vector<string> g(n);
    for(int i = 0; i < n; i++){
        cin >> g[i];
    }
    vvb v(n, vb(m, false));
    string s = decode(0, 0, v, g);
    // cout << "DECODE : " << s << "\n";
    // reverse(s.begin(), s.end());
    n = 3 + (s.size() - 1) * 4;
    m = 100 + (s.size() - 1) * 2;
    // cout << "OUT DIMS : " << n << " " << m << "\n";
    g = vector<string>(n, string(m, ' '));
    pii tl = {s.size() - 1, s.size() - 1};
    pii br = {tl.first + 3 - 1, tl.second + 100 - 1};   //inclusive
    // cout << "TL BR : " << tl.first << " " << tl.second << " " << br.first << " " << br.second << endl;
    //hard code the first character
    bool cchar = s.size() % 2;
    for(int i = tl.first; i <= br.first; i++){
        for(int j = tl.second; j <= br.second; j++){
            g[i][j] = cchar? '#' : '.';
        }
    }
    for(int i = 0; i <= s[0] - 'a'; i++){
        g[br.first - 1][br.second - 1 - i * 2] = !cchar? '#' : '.';
    }
    cchar = !cchar;
    //rest of characters
    for(int sptr = 1; sptr < s.size(); sptr++){
        tl.first --;
        tl.second --;
        br.first += 3;
        br.second ++;
        // cout << "TL BR : " << tl.first << " " << tl.second << " " << br.first << " " << br.second << endl;
        //color it in
        for(int i = tl.second; i <= br.second; i++){
            g[tl.first + 0][i] = cchar? '#' : '.';
            g[br.first - 2][i] = cchar? '#' : '.';
            g[br.first - 1][i] = cchar? '#' : '.';
            g[br.first - 0][i] = cchar? '#' : '.';
        }
        for(int i = tl.first; i <= br.first; i++){
            g[i][tl.second] = cchar? '#' : '.';
            g[i][br.second] = cchar? '#' : '.';
        }
        //do dots
        for(int i = 0; i < s[sptr] - 'a'; i++){
            g[br.first - 1][br.second - 1 - i * 2] = !cchar? '#' : '.';
        }
        cchar = !cchar;
    }
    cout << n << " " << m << "\n";
    for(int i = 0; i < n; i++){
        // cout << "ROW : " << "\n";
        cout << g[i] << "\n";
    }
    
    return 0;
}