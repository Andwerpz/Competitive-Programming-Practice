#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1747D

//doesn't work D:

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    vector<int> pfx(n);
    vector<vector<int>> a(30, vector<int>(n));
    for(int i = 0; i < n; i++){
        int next;
        cin >> next;
        pfx[i] = next;
        for(int j = 0; j < 30; j++) {
            a[j][i] = (next & (1 << j)) == 0? 0 : 1;
        }
    }
    for(int i = 0; i < 30; i++){
        for(int j = 1; j < n; j++){
            a[i][j] += a[i][j - 1];
        }
    }
    for(int i = 1; i < n; i++){
        pfx[i] += pfx[i - 1];
    }
    while(q-- > 0) {
        int l, r;
        cin >> l >> r;
        l--;
        int len = r - l;
        if(len == 1 || len == 2) {
            cout << (pfx[r - 1] - (l == 0? 0 : pfx[l - 1]) == 0? 0 : -1) << "\n";
            continue;
        }
        if(len % 2 == 1){
            cout << (pfx[r - 1] - (l == 0? 0 : pfx[l - 1]) == 0? 0 : 1) << "\n";
            continue;
        }
        cout << "TBD\n";
    }
    
    return 0;
}
