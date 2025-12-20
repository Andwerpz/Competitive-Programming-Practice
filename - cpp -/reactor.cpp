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

//AOC 2025 - Day 11

//just topological sort + dp

vector<string> split(string s, char delim) {
    vector<string> ret;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == delim) continue;
        int r = i;
        while(r != s.size() && s[r] != delim) r ++;
        ret.push_back(s.substr(i, r - i));
        i = r - 1;
    }
    return ret;
}

void solve_p1() {
    vector<string> ids;
    vector<vector<string>> cs;
    {
        string line;
        getline(cin, line);
        while(!cin.eof()) {
            vector<string> tok = split(line, ' ');
            ids.push_back(tok[0].substr(0, tok[0].size() - 1));
            cs.push_back({});
            for(int i = 1; i < tok.size(); i++) cs[cs.size() - 1].push_back(tok[i]);
            getline(cin, line);
        }
    }
    map<string, int> indmp;
    for(int i = 0; i < ids.size(); i++) indmp[ids[i]] = i;
    assert(!indmp.count("out"));
    indmp["out"] = ids.size();
    ids.push_back("out");
    int n = ids.size();
    vvi c(n);
    for(int i = 0; i < n; i++) {
        for(string x : cs[i]) c[i].push_back(indmp[x]);
    }
    vi indeg(n, 0);
    for(int i = 0; i < n; i++) {
        for(int x : c[i]) indeg[x] ++;
    }
    vl dp(n, 0);
    for(int i = 0; i < n; i++) if(ids[i] == "you") dp[i] = 1;
    queue<int> q;
    for(int i = 0; i < n; i++) {
        if(indeg[i] == 0) q.push(i);
    }
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        for(int x : c[cur]) {
            indeg[x] --;
            dp[x] += dp[cur];
            if(indeg[x] == 0) {
                q.push(x);
            }
        }
    }
    ll ans = dp[n - 1];
    cout << "ANS : " << ans << "\n";
}

void solve_p2() {
    vector<string> ids;
    vector<vector<string>> cs;
    {
        string line;
        getline(cin, line);
        while(!cin.eof()) {
            vector<string> tok = split(line, ' ');
            ids.push_back(tok[0].substr(0, tok[0].size() - 1));
            cs.push_back({});
            for(int i = 1; i < tok.size(); i++) cs[cs.size() - 1].push_back(tok[i]);
            getline(cin, line);
        }
    }
    map<string, int> indmp;
    for(int i = 0; i < ids.size(); i++) indmp[ids[i]] = i;
    assert(!indmp.count("out"));
    indmp["out"] = ids.size();
    ids.push_back("out");
    int n = ids.size();
    vvi c(n);
    for(int i = 0; i < n; i++) {
        for(string x : cs[i]) c[i].push_back(indmp[x]);
    }
    vi indeg(n, 0);
    for(int i = 0; i < n; i++) {
        for(int x : c[i]) indeg[x] ++;
    }
    vvl dp(4, vl(n, 0));
    for(int i = 0; i < n; i++) if(ids[i] == "svr") dp[0][i] = 1;
    queue<int> q;
    for(int i = 0; i < n; i++) {
        if(indeg[i] == 0) q.push(i);
    }
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        for(int x : c[cur]) {
            indeg[x] --;
            for(int i = 0; i < 4; i++) {
                int ni = i;
                if(ids[cur] == "fft") ni |= 1;
                if(ids[cur] == "dac") ni |= 2;
                dp[ni][x] += dp[i][cur];
            }
            if(indeg[x] == 0) {
                q.push(x);
            }
        }
    }
    ll ans = dp[3][n - 1];
    cout << "ANS : " << ans << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ifstream in("reactor.in");
    streambuf *cinbuf = cin.rdbuf(); //save old buf
    cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

    // solve_p1();
    solve_p2();
    
    return 0;
}