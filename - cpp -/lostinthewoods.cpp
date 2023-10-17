#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Kattis - lostinthewoods

//the situation is just a markov chain; given that we start at state 1, what's the expected amount of
//turns to move to state n.

//since n <= 20, and the state transition probabilities are at least 1/20, we can just simulate it. 
//each turn will cost around 20^3, which is around 8000, so we can easily afford 10^4 steps. 

vector<vector<ld>> matrix_mul(vector<vector<ld>>& a, vector<vector<ld>>& b) {
    vector<vector<ld>> res(a.size(), vector<ld>(a.size(), 0));
    for(int i = 0; i < a.size(); i++){
        for(int j = 0; j < a.size(); j++){
            for(int k = 0; k < a.size(); k++){
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<int>> c(n, vector<int>(0));
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        c[a].push_back(b);
        c[b].push_back(a);
    }
    vector<vector<ld>> mkv(n, vector<ld>(n, 0));
    for(int i = 0; i < n - 1; i++){
        ld prob = 1.0 / (ld) c[i].size();
        for(int j = 0; j < c[i].size(); j++){
            mkv[i][c[i][j]] = prob;
        }
    }
    mkv[n - 1][n - 1] = 1;
    vector<vector<ld>> cur(n, vector<ld>(n, 0));
    for(int i = 0; i < n; i++){
        cur[i][i] = 1;
    }
    ld ans = 0;
    ld p_sum = 0;
    for(int i = 0; i < 10000; i++){
        cur = matrix_mul(cur, mkv);
        //cout << "I : " << i << "\n";
        // for(int j = 0; j < n; j++){
        //     for(int k = 0; k < n; k++){
        //         cout << cur[j][k] << " ";
        //     }
        //     cout << "\n";
        // }
        ld time = i + 1;
        ld prob = cur[0][n - 1] - p_sum;
        ans += time * prob;
        p_sum += prob;
    }
    cout << fixed << setprecision(10) << ans << "\n";
    
    return 0;
}
