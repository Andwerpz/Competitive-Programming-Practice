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

//2024 ICPC NAQ - L

//can just use brute force backtracking. 

//observe that if there is a direct path to the apple or the tail, then you can always get to the
//apple. 

//need to be careful on the case where the snake is length 2. 

vi dr = {-1, 1, 0, 0};
vi dc = {0, 0, -1, 1};
pii apos;
int dfscnt = 0;
bool sz2 = false;

bool dfs(int cnt, vector<string>& g, deque<pii>& q) {
    dfscnt ++;
    // cout << "GRID : \n";
    // for(int i = 0; i < g.size(); i++){
    //     cout << g[i] << "\n";
    // }
    cnt ++;
    bool ans = false;
    pii tpos = q.front();
    pii hpos = q.back();
    //move the tail
    q.pop_front();
    g[tpos.first][tpos.second] = '.';
    {   
        if(sz2) {
            g[tpos.first][tpos.second] = 's';
        }
        int n = g.size();
        int m = g[0].size();
        vvb v(n, vb(m, false));
        v[hpos.first][hpos.second] = true;
        queue<pii> bq;
        bq.push(hpos);
        while(bq.size() != 0){
            int r = bq.front().first;
            int c = bq.front().second;
            bq.pop();
            if(pii(r, c) == tpos || pii(r, c) == apos) {
                ans = true;
                break;
            }
            for(int i = 0; i < 4; i++){
                int nr = r + dr[i];
                int nc = c + dc[i];
                if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                    continue;
                }
                if(!v[nr][nc] && g[nr][nc] != 's'){
                    v[nr][nc] = true;
                    bq.push({nr, nc});
                }
            }
        }
        // if(ans) {
        //     cout << "DIRECT PATH\n";
        // }
        if(sz2) {
            return ans;
        }
    }
    for(int i = 0; i < 4 && cnt < 100 && !ans; i++){
        int nr = q.back().first + dr[i];
        int nc = q.back().second + dc[i];
        if(nr < 0 || nc < 0 || nr >= g.size() || nc >= g[0].size()) {
            continue;
        }
        if(g[nr][nc] == 'a') {
            ans = true;
            continue;
        }
        if(g[nr][nc] == '.') {
            //move head
            q.push_back({nr, nc});
            g[nr][nc] = 's';
            ans = ans || dfs(cnt, g, q);
            //remove head
            q.pop_back();
            g[nr][nc] = '.';
        }
    }
    //put tail back
    q.push_front(tpos);
    g[tpos.first][tpos.second] = 's';
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int r, c;
    cin >> r >> c;
    vector<string> g(r, string(c, '.'));    //'s' = snake, 'a' = apple
    vector<pair<int, pii>> snakepos;
    for(int i = 0; i < r; i++){
        string line;
        cin >> line;
        for(int j = 0; j < c; j++){
            if(line[j] == 'A'){
                g[i][j] = 'a';
                apos = {i, j};
                continue;
            }
            else if(line[j] != '.') {
                if('0' <= line[j] && line[j] <= '9'){
                    snakepos.push_back({line[j] - '0', {i, j}});
                }
                else {
                    snakepos.push_back({line[j] - 'a' + 10, {i, j}});
                }
                g[i][j] = 's';
            }
        }
    }
    sort(snakepos.begin(), snakepos.end());
    deque<pii> q;
    for(int i = 0; i < snakepos.size(); i++){
        q.push_front(snakepos[i].second);
    }
    bool is_valid = false;
    sz2 = snakepos.size() == 2;
    if(snakepos.size() == 1){
        is_valid = true;
    }
    else if(snakepos.size() == 2){
        if(min(r, c) == 1){
            is_valid = dfs(0, g, q);
        }
        else {
            is_valid = true;
        }
    }
    else {
        is_valid = dfs(0, g, q);
    }
    cout << (is_valid? "1\n" : "0\n");
    // cout << "DFSCNT : " << dfscnt << "\n";

    return 0;
}