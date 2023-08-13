#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1859C

//the maximum possible cost of a length n permutation, disregarding the subtract step, is when the elements are arranged in ascending order;
//1, 2, 3, ..., n. 

//when considering the subtract step, we will only subtract the maximum element. Then, we want to make the maximum element smaller, 
//so we can reverse some suffix of the array. 

//try reversing every suffix of the array, and take the maximum answer. 

ll solve(ll n, ll rev) {
    //cout << "SOLVE : " << n << " " << rev << "\n";
    ll ptr = 1;
    ll ans = 0;
    ll mx = 0;
    for(ll i = 1; i <= n - rev; i++){
        //cout << "I : " << 
        ll next = i * ptr;
        mx = max(mx, next);
        ans += next;
        ptr ++;
    }
    for(ll i = n; i > n - rev; i--){
        ll next = i * ptr;
        mx = max(mx, next);
        ans += next;
        ptr ++;
    }
    ans -= mx;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n;
        cin >> n;
        ll ans = 0;
        for(ll i = 0; i <= n; i++){
            ans = max(ans, solve(n, i));
        }
        cout << ans << "\n";
    }
    
    return 0;
}
