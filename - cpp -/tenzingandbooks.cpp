#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1842B

//We just want to read as many books off the top of each pile. 

int apply(vector<int>& a, int val, int x) {
    for(int i = 0; i < a.size(); i++){
        if(((~x) & a[i])) {
            break;
        }
        val |= a[i];
    }
    return val;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, x;
        cin >> n >> x;
        vector<int> a(n);
        vector<int> b(n);
        vector<int> c(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        for(int i = 0; i < n; i++){
            cin >> b[i];
        }
        for(int i = 0; i < n; i++){
            cin >> c[i];
        }
        int p = 0;
        p = apply(a, p, x);
        p = apply(b, p, x);
        p = apply(c, p, x);
        cout << (p == x? "YES" : "NO") << "\n";
    }
    
    return 0;
}
