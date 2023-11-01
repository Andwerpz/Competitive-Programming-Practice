#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2017 - I

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    
    int m; cin >> m;
    int n; cin >> n;

    vector<vector<bool>> g(26, vector<bool>(26));

    for (int i = 0; i < m; ++i) {
        char a, b; cin >> a >> b;
        int ia = a - 'a';
        int ib = b - 'a';
        g[ia][ib] = true;
    }

    for (int i = 0; i < 26; ++i) {
        g[i][i] = true;
    }

    for (int i = 0; i < 26; ++i) {
        queue<int> q;
        vector<bool> vis(26);
        q.push(i);
        while (q.size()) {
            int v = q.front();
            q.pop();
            if (vis[v]) continue;
            vis[v] = true;

            g[i][v] = true;

            for (int j = 0; j < 26; ++j) {
                if (g[v][j]) {
                    q.push(j);
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        string s1, s2; cin >> s1 >> s2;

        if (s1.size() != s2.size()) {
            cout << "no" << endl;
            continue;
        }
        bool works = true;
        for (int j = 0; j < s1.size(); ++j) {
            // cerr << "j : " << j << " works : " << works << endl;
            if (s1[j] == ' ') {
                if (s2[j] == ' ') continue;
                else {
                    works = false;
                    break;
                }
            }
            int i1 = s1[j] - 'a';
            int i2 = s2[j] - 'a';
            if (!g[i1][i2]) {
                works = false;
            }
        }
        if (works) cout << "yes" << endl;
        else cout << "no" << endl;
    }
    
    return 0;
}
