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

//Codeforces - 1998 E1, E2

//really jank solution, but whatever. 

//i call an element a 'start' if it can become the last one remaining.

//we can consider all prefixes of the array by incrementally adding on the next element to the previous prefix. 
//when we add an element, the number of starts will always increase except if the added element is greater than the 
//sum of the entire previous prefix. Then, the number of starts will get reduced to 1. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int t;
    cin >> t;
    while(t--){
        int n, x;
        cin >> n >> x;
        x --;
        vl a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vl ans(n, 0);
        ll cans = 0;
        stack<array<ll, 5>> s;  //{sum, fcost, bcost, start, borrow}
        s.push({0, 0, 0, 0});
        for(int i = 0; i < n; i++){
            stack<array<ll, 5>> bs;
            s.push({a[i], a[i], a[i], 1, 0});
            while(s.size() >= 2){
                array<ll, 5> cur = s.top();
                s.pop();
                array<ll, 5> prev = s.top();
                s.pop();
                ll c_sum = cur[0];
                ll c_fcost = cur[1];
                ll c_bcost = cur[2];
                ll c_start = cur[3];
                ll c_borr = cur[4];
                ll p_sum = prev[0];
                ll p_fcost = prev[1];
                ll p_bcost = prev[2];
                ll p_start = prev[3];
                ll p_borr = prev[4];
                if(c_sum + c_borr < p_bcost) {
                    //see if we can borrow
                    if(p_sum >= c_fcost) {
                        //inherit borrow from cur
                        s.push({p_sum, p_fcost, p_bcost, p_start, c_borr + c_sum});
                        bs.push(cur);
                        continue;
                    }
                    //can't do anything. 
                    s.push(prev);
                    s.push(cur);
                    break;
                }
                //c_sum + c_borr >= p_bcost
                //can dominate or combine depending on p_sum >= c_fcost
                ll n_sum = c_sum + p_sum;
                ll n_fcost = max(p_fcost, c_fcost - p_sum);
                ll n_bcost = max(c_bcost, p_bcost - c_sum);
                ll n_start = c_start + (p_sum >= c_fcost? p_start : 0);
                ll n_borr = c_borr;
                s.push({n_sum, n_fcost, n_bcost, n_start, n_borr});
            }
            if(s.size() == 1){
                cans = s.top()[3];
            }
            while(bs.size()) {
                s.push(bs.top());
                bs.pop();
            }
            ans[i] = cans;
        }
        for(int i = x; i < n; i++){
            cout << ans[i] << " ";   
        }
        cout << "\n";
    }
    
    return 0;
}