#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//NCPC 2019 - H

//implementation

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int min_temp = 1e9;
    int d = -1;
    for(int i = 0; i < n - 2; i++){
        int temp = max(a[i], a[i + 2]);
        if(temp < min_temp) {
            min_temp = temp;
            d = i + 1;
        }
    }
    cout << d << " " << min_temp << "\n";
    
    return 0;
}
