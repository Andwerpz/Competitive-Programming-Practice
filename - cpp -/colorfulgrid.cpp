#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1898C

//if k is too small, or (n + m - 1) % 2 != k % 2, then it's impossible. 
//otherwise, it's always possible, because n, m >= 3. 

//we can just go around in a loop of length 4 and alternate the coloring of the edges. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m, k;
        cin >> n >> m >> k;
        k ++;
        if(((n + m - 1) % 2) != (k % 2) || n + m - 1 > k) {
            cout << "NO\n";
            continue;
        }
        vector<vector<char>> h_ans(n, vector<char>(m - 1, 'R'));
        vector<vector<char>> v_ans(n - 1, vector<char>(m, 'R'));
        h_ans[0][0] = 'B';
        h_ans[1][0] = 'B';
        v_ans[0][0] = 'R';
        v_ans[0][1] = 'R';
        {
            bool is_red = false;
            for(int i = 1; i < n - 1; i++){
                v_ans[i][0] = (is_red? 'R' : 'B');
                is_red = !is_red;
            }
            for(int i = 0; i < m - 1; i++){
                h_ans[n - 1][i] = (is_red? 'R' : 'B');
                is_red = !is_red;
            }
        }
        {
            bool is_red = false;
            for(int i = 1; i < m - 1; i++){
                h_ans[0][i] = (is_red? 'R' : 'B');
                is_red = !is_red;
            }
            for(int i = 0; i < n - 1; i++){
                v_ans[i][m - 1] = (is_red? 'R' : 'B');
                is_red = !is_red;
            }
        }
        cout << "YES\n";
        for(int i = 0; i < h_ans.size(); i++){
            for(int j = 0; j < h_ans[0].size(); j++){
                cout << h_ans[i][j] << " ";
            }
            cout << "\n";
        }
        for(int i = 0; i < v_ans.size(); i++){
            for(int j = 0; j < v_ans[0].size(); j++){
                cout << v_ans[i][j] << " ";
            }
            cout << "\n";
        }
    }
    
    return 0;
}
