#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//CSES - 1621

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    set<int> s;
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        s.insert(a);
    }
    cout << s.size() << "\n";
    
    return 0;
}
