#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Week 6C

//simple implementation problem

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, h, v;
    cin >> n >> h >> v;
    ll d = 4;
    ll w = max(n - h, h);
    ll l = max(n - v, v);
    cout << d * w * l << "\n";
    
    return 0;
}
