#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSES 1660

//prefix sum + map. 

//the sum over the subarray [l, r] is equal to pfx[r] - pfx[l - 1]. We are interested when pfx[r] - pfx[l - 1] = x. 
//Solving for pfx[l - 1] gives us pfx[l - 1] = pfx[r] - x, so we just need to keep track of how many times pfx[r] - x has shown up before r. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    ll x;
    cin >> n >> x;
    ll sum = 0;
    map<ll, int> m;
    m.insert(pair<ll, int>(0, 1));
    ll ans = 0;
    for(int i = 0; i < n; i++){
        ll next;
        cin >> next;
        sum += next;
        ll req = sum - x;
        if(m.find(req) != m.end()){
            ans += m.find(req) -> second;
        }
        if(m.find(sum) == m.end()){
            m.insert(pair<ll, int>(sum, 0));
        }
        m.find(sum) -> second ++;
    }
    cout << ans << "\n";
    
    return 0;
}
