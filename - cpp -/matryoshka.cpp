#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
int INF = 1e9;

//ICPC World Finals 2013 - H

//O(n^3) 2d dp. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];


    vector<vector<bool>> possi(n, vector<bool> (n));


    for (int i = n-1; i > -1; --i) {
        vector<int> freq(501);
        for (int j = i; j < n; ++j) {
            freq.assign(501, 0);
            for (int k = i; k <= j; ++k) {
                freq[a[k]]++;
            }
            bool works = true;
            bool turned_on = false;
            for (int k = 500; k > 0; --k) {
                if (!freq[k] && turned_on) works = false;
                else if (freq[k] > 1) works = false;
                else if (freq[k] == 1) turned_on = true;
            }
            

            for (int k = i; k < j; ++k) {
                works = works || (possi[i][k] && possi[k+1][j]);
            }
            possi[i][j] = works;
        }
    }

    // cerr << "hey" << endl;

    // for (int i = 0; i < n; ++i) {
    //     for (int j = i; j < n; ++j) {
    //         cerr << possi[i][j] << " ";
    //     }
    //     cerr << endl;
    // }
    // cerr << "hey" << endl;



    vector<vector<vector<int>>> cumu(n, vector<vector<int>> (n, vector<int> (502)));

    for (int i = 0; i < n; ++i) {
        vector<int> freq(501);
        for (int j = i; j < n; ++j) {
            freq[a[j]]++;
            for (int k = 500; k > 0; --k) {
                cumu[i][j][k] = cumu[i][j][k+1] + freq[k];
            }
        }
    }

    // cerr << "hey" << endl;

    vector<vector<int>> mns(n, vector<int> (n));

    for (int i = 0; i < n; ++i) {
        int mn = a[i];
        for (int j = i; j < n; ++j) {
            mn = min(a[j], mn);
            mns[i][j] = mn;
        }
    }

    // cerr << "hey" << endl;


    vector<vector<int>> dp(n, vector<int> (n, INF));


    for (int i = n-1; i > -1; --i) {
        dp[i][i] = 0;
        for (int j = i+1; j < n; ++j) {
            // if (!possi[i][j]) continue;
            for (int k = i; k < j; ++k) {
                int option = dp[i][k] + dp[k+1][j] + cumu[i][k][mns[k+1][j]] + cumu[k+1][j][mns[i][k]];
                dp[i][j] = min(dp[i][j], option);

                if (possi[i][k] && possi[k+1][j]) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j]);
                }
            }
        }
    }

    // cerr << "dp02 : " << dp[0][2] << endl;
    // cerr << "dp36 : " << dp[3][6] << endl;

    if (!possi[0][n-1]) {
        cout << "impossible" << endl;
    } else cout << dp[0][n-1] << endl;
    
    return 0;
}
