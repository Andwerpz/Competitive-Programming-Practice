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

//NCPC 2024 - G

//max flow?

// bool dfs(int a, int L, vector<vector<int>> &g, vector<int> &btoa, vector<int> &A, vector<int> &B) {
//     if (A[a] != L) return 0;
//     A[a] = -1;
//     for(int b : g[a]) if(B[b] == L + 1) {
//         B[b] = 0;
//         if(btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
//             return btoa[b] = a, 1;
//     }
//     return 0;
// }

// int hopcroftKarp(vector<vector<int>> &g, vector<int> &btoa) {
//     int res = 0;
//     vector<int> A(g.size()), B(btoa.size()), cur, next;
//     for(;;) {
//         fill(A.begin(),A.end(), 0);
//         fill(B.begin(),B.end(), 0);
//         cur.clear();
//         for(int a : btoa) if(a != -1) A[a] = -1;
//         for(int a = 0; a < g.size(); a++) {
//             if(A[a] == 0) cur.push_back(a);
//         }
//         for(int lay = 1;; lay++) {
//             bool islast = 0;
//             next.clear();
//             for(int a : cur) {
//                 for(int b : g[a]) {
//                     if(btoa[b] == -1) {
//                         B[b] = lay;
//                         islast = 1;
//                     }
//                     else if(btoa[b] != a && !B[b]) {
//                         B[b] = lay;
//                         next.push_back(btoa[b]);
//                     }
//                 }
//                 if(islast) break;
//                 if(next.empty()) return res;
//                 for(int a : next) A[a] = lay;
//                 cur.swap(next);
//             }
//             for(int a = 0; a < g.size(); a++) {
//                 res += dfs(a, 0, g, btoa, A, B);
//             }
//         }
//     }
// }

bool dfs(int a, int L, vector<vector<int>> &g, vector<int> &btoa, vector<int> &A, vector<int> &B) {
    if(A[a] != L) return 0;
    A[a] = -1;
    for(int b : g[a]) if(B[b] == L + 1) {
        B[b] = 0;
        if(btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
            return btoa[b] = a, 1;
    }
    return 0;
}

int hopcroftKarp(vector<vector<int>> &g, vector<int> &btoa) {
    int res = 0;
    vector<int> A(g.size()), B(btoa.size()), cur, next;
    for(;;) {
        fill(A.begin(),A.end(),0);
        fill(B.begin(),B.end(),0);
        cur.clear();
        for(int a: btoa) if(a != -1) A[a] = -1;
        for(int a = 0; a < g.size(); a++) if(A[a] == 0) cur.push_back(a);
        for(int lay = 1;; lay++) {
            bool islast = 0;
            next.clear();
            for(int a : cur) for(int b : g[a]) {
                if(btoa[b] == -1) {
                    B[b] = lay;
                    islast = 1;
                }
                else if(btoa[b] != a && !B[b]) {
                    B[b] = lay;
                    next.push_back(btoa[b]);
                }
            }
            if(islast) break;
            if(next.empty()) return res;
            for(int a : next) A[a] = lay;
            cur.swap(next);
        }
        for(int a = 0; a < g.size(); a++) 
            res += dfs(a,0,g,btoa,A,B);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<vector<int>> res(n+1,vector<int>(m,-1));

    vector<string> guesses(n);
    for(auto &x : guesses) cin >> x;

    int y = count(guesses[0].begin(), guesses[0].end(), 'Y');
    vector<vector<int>> adj(y,vector<int>(m,1));

    int ok = 1;

    for(int i = 0; i <= n; i++) {
        string s = "";

        if(i == n) {
            s = string(m,'Y');
        } else {
            s = guesses[i];
        }

        vector<vector<int>> graph(y);

        for(int k = 0; k < m; k++) {
            if(s[k] != 'Y') continue;
            for(int j = 0; j < y; j++) {
                if(adj[j][k]) {
                    graph[j].push_back(k);
                }
            }
        }

        // cout << "graph" << endl;
        // for(int i = 0; i < y; i++) {
        //     cout << "i : " << i << " to ";
        //     for(int to : graph[i]) {
        //         cout << to << ", ";
        //     }
        //     cout << endl;
        // }

        vector<int> btoa(m,-1);

        int flow = hopcroftKarp(graph, btoa);
        // cout << "flow : " << flow << endl;
        // cout << "i : " << i << " btoa : ";
        // for(int j = 0; j < m; j++) {
        //     cout << btoa[j] << " \n"[j == m - 1];
        // }
        // cout << endl;

        if(flow != y) {
            ok = 0;
        }

        for(int j = 0; j < m; j++) {
            res[i][j] = btoa[j];
            if(btoa[j] != -1) {
                adj[btoa[j]][j] = 0;
            }
        }
    }

    int id = y;
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j < m; j++) {
            if(res[i][j] == -1) {
                res[i][j] = id++;
            }
        }
    }

    int z; cin >> z;
    if(id > z) {
        ok = 0;
    }

    if(ok) {
        for(int i = 0; i <= n; i++) {
            for(int j = 0; j < m; j++) {
                cout << res[i][j] + 1 << " \n"[j == m - 1];
            }
        }
    } else {
        cout << "Bugged!\n";
    }


    // cerr << "ok" << endl;
    
    return 0;
}