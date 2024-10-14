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
typedef __int128 lll;
// typedef __float128 lld;

//2024 ICPC NAC - J

//lets say that we pick some trip x to run out of space. Then, all trips before x need to make sure that
//there are no subsequences of length a[x] available, and the best way to do that is to put stamps with gap a[x] - 1. 
//so (a[x] - 1) * x + sum(0, x - 1) pages will be taken up, where sum(l, r) denotes the sum of a[l] + ... + a[r]. 

//we can simply try all x and return the smallest one that works. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n, p;
    cin >> n >> p;
    vector<lll> a(n);
    for(int i = 0; i < n; i++){
        ll next;
        cin >> next;
        a[i] = next;
    }
    ll sum = 0;
    int ans = n;
    for(int i = 0; i < n; i++){
        lll rem = p - (a[i] - 1) * (lll) i - sum;
        if(rem < a[i]){
            ans = i;
            break;
        }
        sum += a[i];
    }
    cout << ans << "\n";
    
    return 0;
}