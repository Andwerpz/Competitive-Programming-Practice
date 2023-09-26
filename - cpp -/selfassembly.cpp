#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
using pi = pair<int, int>;

//ICPC World Finals 2013 - A

//we just need to find a cycle. Since we can rotate and reflect all the tiles, as long as there 
//is a cycle, it can grow to infinity. 

vector<vector<vector<pi>>> A2p(27, vector<vector<pi>> (2));
vector<vector<pi>> p2A(41234, vector<pi> (4));
vector<vector<bool>> bad(41234, vector<bool> (4));

bool dfs(int tile, int orie, vector<vector<bool>>& visited) {
    // cerr << "tile : " << tile << " orie : " << orie << endl;
    if (visited[tile][orie]) return true;
    if (bad[tile][orie]) return false;
    bad[tile][orie] = true;
    visited[tile][orie] = true;
    bool res = false;
    for (int i = 0; i < 4; ++i) {
        if (i == orie) continue;
        int Ai = p2A[tile][i].first;
        int opi = p2A[tile][i].second;
        // if (tile == 2) {
        //     cerr << "Ai : " << Ai << " opi : " << opi << endl;
        // }

        while (A2p[Ai][opi ^ 1].size()) {
            auto p = A2p[Ai][opi ^ 1].back();
            if (dfs(p.first, p.second, visited)) return true;
            assert (p == A2p[Ai][opi ^ 1].back());
            A2p[Ai][opi ^ 1].pop_back();
        }

        // for (int i = A2p[Ai][opi ^ 1].size() - 1; i > -1; --i) {

        // }

        // for (auto p : A2p[Ai][opi ^ 1]) {
        //     // cerr << "curr. tile : " << tile << " ori : " << orie << endl;
        //     // cerr <<"next. tile : " << p.first << " orie : " << p.second << endl;
        //     if (dfs(p.first, p.second, visited)) return true;
        // }
        
    }
    visited[tile][orie] = false;
    return res;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        // cerr << "s : " << s << endl;
        for (int j = 0; j < 8; j += 2) {
            char A = s[j];
            char op = s[j+1];
            int Ai;
            if (A == '0') Ai = 26;
            else Ai = A - 'A';
            int opi = (op == '+');
            p2A[i][j/2] = {Ai, opi};
            A2p[Ai][opi].push_back({i, j/2});
        }
    }

    // cerr << "HEY" << endl;


    vector<vector<bool>> visited(n, vector<bool> (4));
    bool cycle = false;
    for (int i = 0; i < n && !cycle; ++i) {
        for (int j = 0; j < 4 && !cycle; ++j) {
            cycle = dfs(i, j, visited);
        }
    }

    // cerr << "hey" << endl;

    if (cycle) cout << "unbounded" << endl;
    else cout << "bounded" << endl;


    return 0;
}
