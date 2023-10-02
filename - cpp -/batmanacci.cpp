#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Kattis - batmanacci

//if n is 1 or 2, the answer is trivial. 

//otherwise, lets consider the kth letter of s_n. The kth letter can either come from s_(n - 2) or s_(n - 1). We can
//determine which it is by computing how long s_(n - 2) is, and seeing if k is less than or greater than the length. 

//then, we recursively reduce n and k, until n == 1 or 2. 

vector<ll> fib;

char solve(ll n, ll k) {
    if(n == 1){
        return 'N';
    }
    if(n == 2){
        return 'A';
    }
    ll pre = fib[n - 2];
    if(k <= pre) {
        return solve(n - 2, k);
    }
    else {
        return solve(n - 1, k - pre);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, k;
    cin >> n >> k;
    fib = vector<ll>(n + 1, 0);
    fib[1] = 1;
    for(int i = 2; i < fib.size(); i++){
        fib[i] = fib[i - 1] + fib[i - 2];
        if(fib[i] > 2e18) {
            fib[i] = 2e18;
        }
    }
    cout << solve(n, k) << "\n";
    
    return 0;
}
