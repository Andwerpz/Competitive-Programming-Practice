#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ACPC Weekly Problem Set 3 Fall 2023 A

//implementation. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll mod = 1e9 + 7;
    int n;
    cin >> n;
    ll a = 1;
    ll b = 1;
    for(int i = 0; i < n - 2; i++){
        ll c = (a + b) % mod;
        swap(a, b);
        swap(b, c);
    }
    cout << a << "\n";
    
    return 0;
}
