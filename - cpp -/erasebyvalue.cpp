#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ARC133A

//just erase the first value that is out of order; by order i mean ascending order
//if there is no value out of order, then just erase the last value. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int rm_val = a[n - 1];
    for(int i = 0; i < n - 1; i++){
        if(a[i] > a[i + 1]) {
            rm_val = a[i];
            break;
        }
    }
    for(int i = 0; i < n; i++){
        if(a[i] == rm_val) {
            continue;
        }
        cout << a[i] << " ";
    }
    cout << "\n";
    
    return 0;
}
