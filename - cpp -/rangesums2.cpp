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
// typedef __int128 lll;
// typedef __float128 lld;

//AtCoder - ARC192C

//Let's say we know some e such that P[e] = 1. Then, we can easily determine P and A in N - 1 queries. Just query 
//every index with e and sort them by sum. Since we are querying prefixes, and A consists entirely of positive integers, 
//sorting by sum also sorts by size. Then, we can take the partial sums to figure out A, and use the ordering to
//figure out P. 

//How can we find such e? We can pick some arbitrary x and query all subarrays of form [x, i]. Then, the i with the 
//largest sum must satisfy P[i] = 1 or P[i] = n. Actually, in the P[i] = n case, we can solve it as if P[i] = 1, and
//after solving we can tell that it is the case because then P[1] > P[2] in our solution, which the problem statement
//guarantees will not happen. 

// vl P, A;
ll query(int s, int t) {    //subarray sum [s, t]
    // s = P[s], t = P[t];
    // if(s > t) swap(s, t);
    // ll sum = 0;
    // for(int i = s; i <= t; i++) sum += A[i];
    // return sum;
    s ++, t ++;
    cout << "? " << s << " " << t << endl;
    ll ans;
    cin >> ans;
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    // P = vl(n), A = vl(n);
    // for(int i = 0; i < n; i++) cin >> P[i];
    // for(int i = 0; i < n; i++) cin >> A[i];
    // for(int i = 0; i < n; i++) P[i] --;
    //find some e where P[e] = 1 or n
    int e = -1;
    ll mxval = -1;
    for(int i = 1; i < n; i++){
        ll val = query(0, i);
        if(val > mxval) mxval = val, e = i;
    }
    //assume P[e] = 1. 
    vector<pll> ord;  //{sum, ind}
    for(int i = 0; i < n; i++){
        if(i == e) continue;
        ord.push_back({query(e, i), i});
    }
    sort(ord.begin(), ord.end());
    vl p(n, -1), a(n, -1);
    p[e] = 0;
    for(int i = 1; i < n; i++) p[ord[i - 1].second] = i;
    //figure out what A[e] is 
    a[0] = ord[1].first - query(ord[0].second, ord[1].second);
    ll psum = a[0];
    for(int i = 1; i < n; i++){
        a[i] = ord[i - 1].first - psum;
        psum += a[i];
    }
    //make sure that P[1] < P[2]
    if(p[0] > p[1]) {
        for(int i = 0; i < n; i++) p[i] = n - 1 - p[i];
        reverse(a.begin(), a.end());
    }
    cout << "! ";
    for(int i = 0; i < n; i++) cout << p[i] + 1 << " ";
    for(int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;
    
    return 0;
}