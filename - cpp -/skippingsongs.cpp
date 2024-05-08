#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//UTPC Spring 2024 Open Contest - A

//implementation. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    getline(cin, a[0]);
    for(int i = 0; i < n; i++){
        getline(cin, a[i]);
    }
    int ptr = 0;
    for(int i = 0; i < m; i++){
        int next;
        cin >> next;
        ptr = (ptr + next) % n;
        cout << a[ptr] << "\n";
        ptr = (ptr + 1) % n;
    }
    
    return 0;
}
