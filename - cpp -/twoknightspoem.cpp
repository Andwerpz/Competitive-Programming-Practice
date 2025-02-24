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

//2014 NAIPC - J

//implementation. 

//turn this into a connectivity problem. Model the current state as a node in a graph, and only add edges
//where there is a valid move. 

//a state is described by [num letters typed][knight 1 position][knight 2 position]
//to make transitions simpler, we can just say that only knight 1 can move, and introduce a new operation:
//the knights can swap position without typing anything. 

vector<string> key = {
    "q", "w", "e", "r", "t", "y", "u", "i", "o", "p",
    "a", "s", "d", "f", "g", "h", "j", "k", "l", ";",
    "z", "x", "c", "v", "b", "n", "m", ",", ".", "/",
    "",  "",  " ", " ", " ", " ", " ", " ", "",  "",
};

vector<string> skey = {
    "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
    "A", "S", "D", "F", "G", "H", "J", "K", "L", ":",
    "Z", "X", "C", "V", "B", "N", "M", "<", ">", "?",
    "",  "",  " ", " ", " ", " ", " ", " ", "",  "",
};

vi dr = {-2, -2, -1, -1, 1, 1, 2, 2};
vi dc = {-1, 1, -2, 2, -2, 2, -1, 1};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    //precompute knight moves
    vvi kc(40);
    for(int i = 0; i < 40; i++){
        int r = i / 10, c = i % 10;
        for(int j = 0; j < 8; j++){
            int nr = r + dr[j];
            int nc = c + dc[j];
            if(nr < 0 || nc < 0 || nr >= 4 || nc >= 10) continue;
            int nind = nr * 10 + nc;
            kc[i].push_back(nind);
            // cout << "KMOVE : " << i << " " << nind << "\n";
        }
    }
    while(true) {
        string s;
        getline(cin, s);
        if(s == "*") break;
        // cout << "S : " << s << "\n";
        int n = s.size();
        //build graph. [next letter][first knight ind][second knight ind]
        int idptr = 0;
        vector<vvi> id(n + 1, vvi(40, vi(40)));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < 40; j++){
                for(int k = 0; k < 40; k++){
                    id[i][j][k] = idptr ++;
                }
            }
        }
        vvi c(idptr);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < 40; j++){
                for(int k = 0; k < 40; k++){
                    //knights can always swap
                    c[id[i][j][k]].push_back(id[i][k][j]);
                    //check which moves are valid for the first knight
                    for(int _ = 0; _ < kc[j].size(); _++) {
                        int nind = kc[j][_];
                        if(nind == k) continue; //can't be on the same position
                        if(key[nind] == "") {
                            //landed on shift
                            c[id[i][j][k]].push_back(id[i][nind][k]);
                            continue;
                        }
                        string nc = key[k] == ""? skey[nind] : key[nind];
                        if(nc[0] == s[i]) {
                            //landed on correct character
                            c[id[i][j][k]].push_back(id[i + 1][nind][k]);
                            continue;
                        }
                    }
                }
            }
        }
        //do bfs
        vb v(idptr, false);
        int start = id[0][30][39];
        queue<int> q;
        q.push(start);
        v[start] = true;
        while(q.size() != 0){
            int cur = q.front();
            q.pop();
            for(int x : c[cur]) if(!v[x]) v[x] = true, q.push(x);
        }
        bool ans = false;
        for(int i = 0; i < 40; i++){
            for(int j = 0; j < 40; j++){
                if(v[id[n][i][j]]) ans = true;
            }
        }
        cout << (ans? 1 : 0) << "\n";
    }
    
    return 0;
}