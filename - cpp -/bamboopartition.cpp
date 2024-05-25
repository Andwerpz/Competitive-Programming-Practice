#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 830C

//so, the solution complexity is O(sqrt(10^9) * n^2), which comes out to around 10^(8.5). Even if i came up with this
//solution, there's no way i would've thought it would not TLE. 

//first, the problem is asking us to find the maximum d for which this inequality is true:
//sum(d * ceil(a[i] / d) - a[i]) <= k
//we can rearrange this to become d * sum(ceil(a[i] / d)) <= k + sum(a[i])
//now, since the right side of the equation is a constant, we are only interested in the behaviour of the left
//side. Note that as d increases, sum(ceil(a[i] / d)) will monotonically decrease. And since it has the ceil function,
//it will look like a bunch of discrete steps 

//Exactly how many times will sum(ceil(a[i] / d)) decrease? If we look at some arbitrary positive integer x, ceil(x / d)
//will decrease around sqrt(x) times, so we can say that sum(ceil(a[i] / d)) will decrease n * sqrt(max(a[i])) times. 

//so to find the maximum d, we just need to find the starting points of each segment of sum(ceil(a[i] / d)), and try
//all of them out. 

ll ceil_div(ll a, ll b){
    return (a + b - 1) / b;
}

bool is_valid(vector<ll>& a, ll k, ll d) {
    ll sum = 0;
    for(int i = 0; i < a.size(); i++){
        sum += d * ceil_div(a[i], d) - a[i];
    }
    return sum <= k;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n);
    vector<ll> b(0);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        for(int j = 1; j * j <= a[i]; j++){
            b.push_back(j);
            b.push_back(ceil_div(a[i], j));
        }
        k += a[i];
    }
    sort(b.begin(), b.end());
    ll ans = 1;
    for(int i = 0; i < b.size(); i++){
        if(i != 0 && b[i] == b[i - 1]){
            continue;
        }
        ll d = b[i];
        ll divsum = 0;
        for(int j = 0; j < n; j++){
            divsum += ceil_div(a[j], d);
        }
        if(k / divsum >= d){
            ans = max(ans, k / divsum);
        }
    }
    cout << ans << "\n";
    
    return 0;
}