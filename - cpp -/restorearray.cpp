#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 1028E

//this problem is overrated D:

//first, if the entire array is the same value, then the only way it will create a valid array is if it's entirely 0s. 

//otherwise, there must exist some value which is greater than the previous value in the array, or b[i] > b[i - 1]. 
//We can set a[i] = b[i], and a[i - 1] = a[i] * 1e6 + b[i - 1] (1e6 is just an arbitrarily high number). 

//from there, we just go around to the remaining numbers and set them. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vl b(n);
    for(int i = 0; i < n; i++){
        cin >> b[i];
    }
    bool all_zero = true;
    for(int i = 0; i < n; i++){
        if(b[i]) {
            all_zero = false;
        }
    }
    if(all_zero){
        cout << "YES\n";
        for(int i = 0; i < n; i++){
            cout << "1 ";
        }
        cout << "\n";
        return 0;
    }
    int start = -1;
    for(int i = 0; i < n; i++){
        if(b[i] < b[(i + 1) % n]) {
            start = (i + 1) % n;
        }
    }
    if(start == -1){
        cout << "NO\n";
        return 0;
    }
    vl a(n);
    a[start] = b[start];
    int ptr = start;
    ptr = (ptr - 1 + n) % n;
    a[ptr] = 1e6 * a[start] + b[ptr];
    for(int i = 2; i < n; i++){
        int prev = ptr;
        ptr = (ptr - 1 + n) % n;
        a[ptr] = a[prev] + b[ptr];
    }
    cout << "YES\n";
    for(int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
    cout << "\n";
    
    return 0;
}