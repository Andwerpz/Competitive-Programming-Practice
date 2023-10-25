#include <bits/stdc++.h>
typedef long long ll;
// typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2016 K

//we came up with a 3d dp approach, but a greedy one should be sufficient due to the problem structure. 

/*
dp[i][j][k]

i - the current quote we are on
j - the current depth we are on
k (0/1) - have we reached level  yet

store - true / false
*/


bool solve_dp(vector<int>& a, int depth, vector<vector<vector<bool>>>& dp) {


    
    int n = a.size();

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= depth+1; ++j) {
            dp[i][j][0] = 0;
            dp[i][j][1] = 0;
        }
    }

    dp[0][depth][0] = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= depth; ++j) {
            if (a[i] < j) {
                continue;
            }

            if (dp[i][j][0]) {
                // still going down
                if (!j) {
                    dp[i][j+1][1] = 1;
                    continue;
                }

                // going down
                dp[i + j][j-1][0] = 1;
            }

            if (dp[i][j][1]) {
                // going up
                if (a[i] >= j) {
                    dp[i + j][j+1][1] = 1;
                }
                
                if (j != depth) {
                    dp[i+j][j][0] = 1;
                }
            }
            
        }
    }

    // for (auto v : dp) {
    //     for (auto d : v) {
    //         for (auto x : d) {
    //             cerr << x << " ";
    //         }
    //         cerr << ", ";
    //     }
    //     cerr << endl;
    // }

    return dp[n][depth+1][1];

}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; 
    cin >> n;

    vector<int> qs(n);
    int s = 0;
    for (int i = 0; i < n; ++i) {
        cin >> qs[i];
        s += qs[i];
    }


    vector<int> a(s);
    int end = -1;
    for (int i = 0; i < n; ++i) {
        end += qs[i];
        int cnt = 1;
        for (int j = end; j > end-qs[i]; --j) {
            a[j] = cnt++;
        }
    }

    vector<vector<vector<bool>>> dp(a.size()+1, vector<vector<bool>>(100+2, vector<bool>(2)));


    // for (auto x : a) cerr << x << " ";
    // cerr << endl;

    for (int i = 100; i > 0; --i) {
        if (solve_dp(a, i, dp)) {
            cout << i << endl;
            return 0;
        }
    }


    cout << "no quotation" << endl;
    
    return 0;
}
