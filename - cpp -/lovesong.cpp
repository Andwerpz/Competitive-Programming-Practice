#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces 727B

//simple pfx sum problem. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<int> pfx(n + 1);
    for(int i = 0; i < n; i++){
        pfx[i + 1] = pfx[i] + (s[i] - 'a') + 1;
    }
    for(int i = 0; i < q; i++){
        int l, r;
        cin >> l >> r;
        cout << pfx[r] - pfx[--l] << "\n";
    }
    
    return 0;
}
