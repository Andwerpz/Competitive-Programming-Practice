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
    string line;
    getline(cin, line);
    int ans = 0;
    while(!cin.eof()) {
        vector<string> tok = split(line, ' ');
        string gs = tok[0].substr(1, tok[0].size() - 2);
        int B = gs.size();
        int goal = 0;
        for(int i = 0; i < B; i++) {
            if(gs[i] == '#') goal ^= (1 << i);
        }
        vi mv;
        for(int i = 1; i < tok.size() - 1; i++) {
            vector<string> inds = split(tok[i].substr(1, tok[i].size() - 2), ',');
            int move = 0;
            for(int j = 0; j < inds.size(); j++) move ^= (1 << stoi(inds[j]));
            mv.push_back(move);
        }
        vi dist((1 << B), 1e9);
        dist[0] = 0;
        priority_queue<pii> q;  //{-dist, state};
        q.push({0, 0});
        while(q.size() != 0){
            int cdist = -q.top().first;
            int cur = q.top().second;
            q.pop();
            if(cdist != dist[cur]) continue;
            for(int i = 0; i < mv.size(); i++) {
                int next = cur ^ mv[i];
                int ndist = cdist + 1;
                if(ndist < dist[next]) {
                    dist[next] = ndist;
                    q.push({-ndist, next});
                }
            }
        }
        ans += dist[goal];
        getline(cin, line);
    }
    cout << "ANS : " << ans << "\n";
}

int lsig_bit(int x) {
    for(int i = 0; i < 30; i++) if(x & (1 << i)) return i;
    assert(false);
    return -1;
}

void solve_p2() {
    string line;
    getline(cin, line);
    int ans = 0;
    while(!cin.eof()) {
        vector<string> tok = split(line, ' ');
        vi ga;
        {
            vector<string> gsa = split(tok[tok.size() - 1].substr(1, tok[tok.size() - 1].size() - 2), ',');
            for(int i = 0; i < gsa.size(); i++) ga.push_back(stoi(gsa[i]));
        }
        int B = ga.size();
        vi mv;
        for(int i = 1; i < tok.size() - 1; i++) {
            vector<string> inds = split(tok[i].substr(1, tok[i].size() - 2), ',');
            int move = 0;
            for(int j = 0; j < inds.size(); j++) move ^= (1 << stoi(inds[j]));
            mv.push_back(move);
        }
        sort(mv.begin(), mv.end(), [](int a, int b) -> bool {
            return __builtin_popcount(a) > __builtin_popcount(b);
            // return lsig_bit(a) < lsig_bit(b);
        });
        //for each value, figure out which move has the 'last responsibility' for it
        vvi lr(mv.size());
        {
            vi v(B, false);
            for(int i = mv.size() - 1; i >= 0; i--) {
                for(int j = 0; j < B; j++) if(mv[i] & (1 << j) && !v[j]) {
                    v[j] = true;
                    lr[i].push_back(j);
                }
            }
        }
        //for each value, what's the largest popcount in the suffix
        vi mpc(mv.size());
        for(int i = 0; i < mv.size(); i++) mpc[i] = __builtin_popcount(mv[i]);
        for(int i = (int) mv.size() - 2; i >= 0; i--) mpc[i] = max(mpc[i], mpc[i + 1]);
        //calc upper bound on moves
        int cans = 0;
        for(int i = 0; i < B; i++) cans += ga[i];
        int mn_pc = 1e9;
        for(int i = 0; i < mv.size(); i++) mn_pc = min(mn_pc, __builtin_popcount(mv[i]));
        cans = (cans + mn_pc - 1) / mn_pc;
        ll itercnt = 0;
        function<void(int, int)> dfs = [&](int ind, int cmv) -> void {
            // cout << "DFS : " << ind << " " << cmv << " ";
            // for(int i = 0; i < B; i++) cout << ga[i] << " ";
            // cout << endl;
            itercnt ++;
            if(itercnt % 1000000 == 0) cout << "ITER : " << itercnt << endl;
            if(ind == mv.size()) {
                for(int i = 0; i < B; i++) {
                    if(ga[i]) assert(false);
                }
                if(cmv < cans) {
                    cout << "NEW BEST : " << cmv << endl;
                }
                cans = min(cans, cmv);
                return;
            } 
            //compute lower bound on number of moves that this subtree can get
            //if lower bound is > cur best, terminate
            {
                int lb = 0;
                //max out of all ga 
                {
                    int clb = 0;
                    for(int i = 0; i < B; i++) clb = max(clb, ga[i]);
                    lb = max(lb, clb);
                }
                //sum over all ga divided by max popcount left
                {
                    int clb = 0;
                    for(int i = 0; i < B; i++) clb += ga[i];
                    clb = (clb + mpc[ind] - 1) / mpc[ind];
                    lb = max(lb, clb);
                }
                lb += cmv;
                if(lb > cans) return;
            }
            //if this button has last responsibility for some bit, the amount of moves is set
            if(lr[ind].size() != 0) {
                int mxrmv = 0;
                for(int x : lr[ind]) mxrmv = max(mxrmv, ga[x]);
                bool valid = true;
                for(int i = 0; i < B; i++) if(mv[ind] & (1 << i) && ga[i] < mxrmv) valid = false;
                if(!valid) return;
                for(int i = 0; i < B; i++) if(mv[ind] & (1 << i)) ga[i] -= mxrmv;
                dfs(ind + 1, cmv + mxrmv);
                for(int i = 0; i < B; i++) if(mv[ind] & (1 << i)) ga[i] += mxrmv;
                return;
            }

            //recurse to next state
            int ptr = 1e9;
            for(int i = 0; i < B; i++) if(mv[ind] & (1 << i)) ptr = min(ptr, ga[i]);
            for(int i = 0; i < B; i++) if(mv[ind] & (1 << i)) ga[i] -= ptr;
            while(ptr >= 0) {
                dfs(ind + 1, cmv + ptr);
                if(ptr == 0) break;
                ptr --;
                for(int i = 0; i < B; i++) if(mv[ind] & (1 << i)) ga[i] ++;
            }
            // cout << "BACKTRACK" << endl;
            // for(int i = 0; i < B; i++) if(mv[ind] & (1 << i)) ga[i] += ptr;
        };

        cout << "SOLVING : " << line << endl;

        dfs(0, 0);
        ans += cans;

        cout << "SOLVED : " << cans << endl;
        
        getline(cin, line);
    }
    cout << "ANS : " << ans << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ifstream in("factory.in");
    streambuf *cinbuf = cin.rdbuf(); //save old buf
    cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

    // solve_p1();
    solve_p2();
    
    return 0;
}