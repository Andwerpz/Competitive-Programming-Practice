#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 02 G

//you just need to use a set as a binary search tree to find the ceil. 

//i think the intended solution is to do binary search across an array. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    ll ans = 0;
    set<ll> s;
    for(int i = 0; i < n; i++){
        ll next;
        cin >> next;
        s.insert(next);
    }
    for(int i = 0; i < m; i++){
        ll next;
        cin >> next;
        ll can = *s.upper_bound(next - 1);
        ans += can - next;
    }
    cout << ans << "\n";
    
    return 0;
}
