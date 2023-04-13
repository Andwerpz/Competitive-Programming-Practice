#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1435B

//since all the numbers are unique, you can use all of the rows, and one column to figure out a unique matrix. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, m;
        cin >> n >> m;
        vector<vector<int>> a(n, vector<int>(m));
        vector<vector<int>> b(m, vector<int>(n));
        map<int, int> rm;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cin >> a[i][j];
                rm.insert({a[i][j], i});
            }
        }
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                cin >> b[i][j];
            }
        }
        for(int i = 0; i < n; i++){
            int r = rm.find(b[0][i]) -> second;
            for(int j = 0; j < m; j++){
                cout << a[r][j] << " ";
            }
            cout << "\n";
        }
    }
    
    return 0;
}
