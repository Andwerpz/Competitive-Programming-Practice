#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1894D

//note that we can never decrease the LIS, only increase it. 
//we just want the elements we insert to not contribute to the existing LIS. 

//i came up with some weird greedy stuff that seems to work. 

//first, sort b in descending order, and compute the suffix maximum array for a. 
//then, iterate from 0 to n - 1, and keep track of a b pointer; b_ptr. Then, for each element of the suffix maximum
//array, sfx, while(b[b_ptr] >= sfx[i]), add b[b_ptr] to c. Otherwise, add a[i]. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<int> a(n);
        vector<int> b(m);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        for(int i = 0; i < m; i++){
            cin >> b[i];
        }
        sort(b.rbegin(), b.rend());
        vector<int> sfx(n, 0);
        sfx[n - 1] = a[n - 1];
        for(int i = n - 2; i >= 0; i--){
            sfx[i] = max(sfx[i + 1], a[i]);
        }
        int b_ptr = 0;
        for(int i = 0; i < n; i++){
            while(b_ptr != m && b[b_ptr] >= sfx[i]) {
                cout << b[b_ptr ++] << " ";
            }
            cout << a[i] << " ";
        }
        while(b_ptr != m) {
            cout << b[b_ptr ++] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
