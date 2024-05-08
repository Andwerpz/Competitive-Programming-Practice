#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//UTPC 04-05-2023 - G

//this problem can be solved with range increment, min query segment tree, but we can be more clever and 
//solve with just a priority queue. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    priority_queue<ll> q;
    for(int i = 0; i < n; i++){
        ll a;
        cin >> a;
        q.push(a);
    }
    ll take_sum = 0;
    ll b_sum = 0;
    for(int i = 0; i < n; i++){
        ll b;
        cin >> b;
        b_sum += b;
        ll next = q.top();
        q.pop();
        ll act = next + b_sum;
        ll take = act / 2;
        take_sum += take;
        q.push(next - take);
    }
    ll ans = 0;
    while(q.size() != 0){
        ans += q.top() + b_sum;
        q.pop();
    }
    cout << ans << "\n";
    
    return 0;
}
