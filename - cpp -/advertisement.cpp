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

//CSES - 1142

//classic monotonic stack problem. 

//note that any optimally placed advertisement must 'max out' one of the boards along it's width. 
//if it doesnt, then it's trivial to improve the answer by just making the advertisement taller. 

//so for every board, given that it's the board that gets 'maxed out', what is the widest advertisement that
//we can place? We just need to find the first element to the right and to the left that are smaller
//than the board in question.

//both these things can be found in O(n) for all boards using monotonic stack, leading to an overall O(n) solution.

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vl a(n), fl(n), fr(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    {
        stack<pll> s;
        s.push({0, -1});
        for(int i = 0; i < n; i++){
            while(s.top().first >= a[i]) {
                s.pop();
            }
            fl[i] = s.top().second;
            s.push({a[i], i});
        }
    }
    {
        stack<pll> s;
        s.push({0, n});
        for(int i = n - 1; i >= 0; i--){
            while(s.top().first >= a[i]){
                s.pop();
            }
            fr[i] = s.top().second;
            s.push({a[i], i});
        }
    }
    ll ans = 0;
    for(int i = 0; i < n; i++){
        ll len = fr[i] - fl[i] - 1;
        ans = max(ans, len * a[i]);
    }
    cout << ans << "\n";
    
    return 0;
}