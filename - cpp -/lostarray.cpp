#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

ll gcd(ll a, ll b) {
    return b == 0? a : gcd(b, a % b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, k;
    cin >> n >> k;
    ll lcm = (n * k) / gcd(n, k);
    if((lcm / n) % 2 == 0){
        cout << "-1" << endl;
        return 0;
    }
    int ptr = 0;
    int ans = 0;
    for(int i = 0; i < lcm / k; i++){
        cout << "? ";
        for(int j = 0; j < k; j++){
            cout << (ptr + 1) << " ";
            ptr = (ptr + 1) % n;
        }
        cout << endl;
        int next;
        cin >> next;
        ans ^= next;
    }
    cout << "! " << ans << endl;
    
    return 0;
}
