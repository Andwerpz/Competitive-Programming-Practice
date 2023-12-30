#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 222B

//we don't have to move the actual data around, instead for each row and column, keep track of what data is
//actually in there. When we swap rows or columns, we can just swap the reference indexes. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> a(n, vector<int>(m, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> a[i][j];
        }
    }
    vector<int> r(n), c(m);
    for(int i = 0; i < n; i++){
        r[i] = i;
    }
    for(int i = 0; i < m; i++){
        c[i] = i;
    }
    while(k--) {
        string s;
        int x, y;
        cin >> s >> x >> y;
        x --;
        y --;
        if(s == "r"){
            swap(r[x], r[y]);
        }
        else if(s == "c"){
            swap(c[x], c[y]);
        }
        else if(s == "g") {
            cout << a[r[x]][c[y]] << "\n";
        }
    }
    
    return 0;
}
