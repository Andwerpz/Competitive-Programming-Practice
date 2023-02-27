#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 06 A

//pretty much like the matrix multiplication problem, but it now matters the type of product. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int k;
    cin >> k;
    map<char, int> m;
    map<int, char> rm;
    for(int i = 0; i < k; i++){
        char c;
        cin >> c;
        m.insert({c, i});
        rm.insert({i, c});
    }
    vector<vector<int>> cost(k, vector<int>(k, 0));
    vector<vector<int>> prod(k, vector<int>(k, 0));
    for(int i = 0; i < k; i++){
        for(int j = 0; j < k; j++){
            string s;
            cin >> s;
            prod[i][j] = m.find(s[s.size() - 1]) -> second;
            cost[i][j] = stoi(s.substr(0, s.size() - 2));
        }
    }
    int t;
    cin >> t;
    while(t-- > 0){
        string s;
        cin >> s;
        int n = s.size();
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            a[i] = m.find(s[i]) -> second;
        }
        //starting index
        //ending index
        //result char
        vector<vector<vector<ll>>> dp(n, vector<vector<ll>>(n, vector<ll>(k, 1000000000)));
        for(int i = 0; i < n; i++){
            dp[i][i][a[i]] = 0;
        }
        for(int i = 1; i < n; i++){
            for(int j = 0; j < n - i; j++){
                //consider the segment [j, j + i]
                int l = j;
                int r = j + i;
                //cout << l << " " << r << "\n";
                for(int mid = l; mid < r; mid++){
                    //two segments, [l, mid], [mid + 1, r]
                    int l1 = l;
                    int l2 = mid;
                    int r1 = mid + 1;
                    int r2 = r;
                    //cout << l1 << " " << l2 << " " << r1 << " " << r2 << "\n";
                    for(int c1 = 0; c1 < k; c1++){
                        for(int c2 = 0; c2 < k; c2++){
                            int cProd = prod[c1][c2];
                            dp[l][r][cProd] = min(dp[l][r][cProd], dp[l1][l2][c1] + dp[r1][r2][c2] + cost[c1][c2]);
                            //cout << dp[l][r][cProd] << "\n";
                        }
                    }
                }
            }
        }
        ll minVal = 1000000000;
        int ind = -1;
        for(int i = 0; i < k; i++){
            ll nextVal = dp[0][n - 1][i];
            if(nextVal < minVal) {
                ind = i;
                minVal = nextVal;
            }
        }
        cout << minVal << "-" << rm.find(ind) -> second << "\n";
    }
    
    return 0;
}
