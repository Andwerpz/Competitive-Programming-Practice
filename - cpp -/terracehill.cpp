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

//CTU Open 2021 - E

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a)
        cin >> x;
    
    stack<pii> st;

    ll cnt = 0;

    for (int i = 0; i < n; ++i) {
        while (st.size() && st.top().first < a[i])
            st.pop();
        
        if (st.size() && st.top().first == a[i]) {
            cnt += i - st.top().second - 1;
        }

        st.push({a[i], i});
    }

    cout << cnt << endl;
    
    return 0;
}