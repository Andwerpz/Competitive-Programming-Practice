#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Kattis - pebblepuzzle

int check(vector<vector<bool>> a, vector<vector<bool>> b, int a_ind, int b_ind) {
    for(int i = 0; i < a.size(); i++){
        if(a[i][a_ind] != b[i][b_ind]) {
            for(int j = 0; j < a[0].size(); j++){
                a[i][j] = !a[i][j];
            }
        }
    }
    vector<string> a_t(a[0].size(), string(a.size(), 0)), b_t(b[0].size(), string(b.size(), 0));
    for(int i = 0; i < a.size(); i++){
        for(int j = 0; j < a[0].size(); j++){
            a_t[j][i] = a[i][j];
            b_t[j][i] = b[i][j];
        }
    }
    sort(a_t.begin(), a_t.end(), [](string& a, string& b) -> int {
        return a < b;
    });
    sort(b_t.begin(), b_t.end(), [](string& a, string& b) -> int{
        return a < b;
    });
    return a_t == b_t;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<vector<bool>> a(n, vector<bool>(m)), b(n, vector<bool>(m));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                string s;
                cin >> s;
                a[i][j] = s == "BLUE";
            }
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                string s;
                cin >> s;
                b[i][j] = s == "BLUE";
            }
        }
        int ans = false;
        for(int i = 0; i < m; i++){
            ans = ans | check(a, b, 0, i);
        }
        cout << (ans? "YES" : "NO") << "\n";
    }
    
    return 0;
}
