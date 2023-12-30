#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ARC132A

//the property is that if the sum of the amounts in the row and column of a cell exceed n, then that cell needs black.

//this property can be easily seen in the case where the row and column values are sorted. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> r(n);
    for(int i = 0; i < n; i++){
        cin >> r[i];
    }
    vector<int> c(n);
    for(int i = 0; i < n; i++){
        cin >> c[i];
    }
    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        cout << (r[a] + c[b] > n? "#" : ".");
    }
    cout << "\n";
    
    return 0;
}
