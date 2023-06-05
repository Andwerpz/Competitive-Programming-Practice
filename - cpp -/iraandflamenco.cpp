#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1833F

//if all the people in the dance have to be unique, and the maximum pairwise difference between any two people
//is strictly less than m, the number of people in the dance, then we are restricted to putting continuous increasing 
//sequences of people in dances. 

//ex: [1, 2, 3, 4, 5] is valid, but [1, 2, 4, 5] is not. In the second one, 3 was skipped, making it not valid. 

//thus, we can just sort the array of people, and count for each skill level, how many people there are. Then just use sliding 
//window of size m, and multiply for each skill level in the window, how many people each has. 

ll mod = 1e9 + 7;

ll add(ll a, ll b) {
    return (a + b) % mod;
}

ll sub(ll a, ll b) {
    ll ans = a - b;
    if(ans < 0){
        ans += mod;
    }
    return ans;
}

ll mul(ll a, ll b) {
    return (a * b) % mod;
}

ll pow(ll a, ll b) {
    if(b == 0){
        return 1;
    }
    ll ans = pow(a, b / 2);
    ans = mul(ans, ans);
    if(b % 2 == 1) {
        ans = mul(ans, a);
    }
    return ans;
}

ll divide(ll a, ll b){
    return mul(a, pow(b, mod - 2));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, m;
        cin >> n >> m;
        vector<int> a(n, 0);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        vector<vector<ll>> seg(0);
        seg.push_back(vector<ll>(1, 1));
        for(int i = 1; i < n; i++){
            if(a[i] == a[i - 1]) {
                seg[seg.size() - 1][seg[seg.size() - 1].size() - 1] ++;
            }
            else if(a[i] - 1 == a[i - 1]) {
                seg[seg.size() - 1].push_back(1);
            }
            else {
                seg.push_back(vector<ll>(1, 1));
            }
        }
        ll ans = 0;
        for(int i = 0; i < seg.size(); i++){
            vector<ll> arr = seg[i];
            if(arr.size() < m) {
                continue;
            }
            ll cnt = 1;
            for(int i = 0; i < m; i++){
                cnt = mul(cnt, arr[i]);
            }
            ans = add(ans, cnt);
            for(int i = m; i < arr.size(); i++){
                cnt = divide(cnt, arr[i - m]);
                cnt = mul(cnt, arr[i]);
                ans = add(ans, cnt);
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
