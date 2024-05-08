#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Codeforces - 1934D1

//you could probably solve this in like 10 lines, but i was lazy D:

//if the most significant bits of n and m match, then it's always possible. Since n > m, if we start
//comparing bits from most significant to least significant, the first bit that differs is going to be n is
//1 and m = 0. We can just turn this bit in n off, and use it to fix the rest of n to be equal to m. 

//if the most significant bits don't match, then we can try to make them match. This is possible if the second
//most significant bit in n is >= most significant bit in m. If this is true, we can actually do it in one operation.

//now, n is guaranteed to have the most significant bit of m, and from here we can use the same technique as
//the first case. 

vector<bool> bools_xor(vector<bool> a, vector<bool> b){
    vector<bool> ans(63, false);
    for(int i = 0; i < ans.size(); i++){
        ans[i] = a[i] ^ b[i];
    }
    return ans;
}

vector<bool> ll_to_bools(ll val) {
    vector<bool> ans(63, false);
    for(int i = ans.size() - 1; i >= 0; i--){
        ans[i] = val % 2;
        val /= 2;
    }
    return ans;
}

ll bools_to_ll(vector<bool>& bools) {
    ll ans = 0;
    for(int i = 0; i < bools.size(); i++){
        ans *= 2;
        ans += bools[i];
    }
    return ans;
}

void print_bools(vector<bool>& a) {
    for(int i = 0; i < a.size(); i++){
        cout << a[i] << " ";
    }
    cout << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n, m;
        cin >> n >> m;
        //if n is power of 2, it's impossible
        {
            ll tmp = n;
            while(tmp % 2 == 0){
                tmp /= 2;
            }
            if(tmp == 1){
                cout << "-1\n";
                continue;
            }
        }
        vector<bool> m_bools = ll_to_bools(m);
        vector<bool> n_bools = ll_to_bools(n);
        vector<ll> ans;
        ans.push_back(bools_to_ll(n_bools));
        int n_sig = -1;
        int m_sig = -1;
        for(int i = 0; i < n_bools.size(); i++){
            if(n_sig == -1 && n_bools[i]) {
                n_sig = i;
            }
            if(m_sig == -1 && m_bools[i]) {
                m_sig = i;
            }
        }
        //make the most significant bits match
        if(n_sig != m_sig) {
            // print_bools(n_bools);
            // print_bools(m_bools);
            int n_2sig = -1;
            for(int i = n_sig + 1; i < n_bools.size(); i++){
                if(n_2sig == -1 && n_bools[i]) {
                    n_2sig = i;
                    break;
                }
            }
            if(n_2sig == -1 || n_2sig > m_sig) {
                cout << "-1\n";
                continue;
            }
            vector<bool> op(63, false);
            for(int i = 0; i < op.size(); i++){
                if(i < n_2sig && n_bools[i]) {
                    op[i] = true;
                }
                else if(i > n_2sig && (n_bools[i] != m_bools[i])) {
                    op[i] = true;
                }
            }
            // cout << "N2SIG : " << n_2sig << "\n";
            // print_bools(op);
            n_bools = bools_xor(n_bools, op);
            ans.push_back(bools_to_ll(n_bools));
            op = vector<bool>(63, false);
            if(n_2sig != m_sig) {
                //remove it
                op[n_2sig] = true;
                n_bools = bools_xor(n_bools, op);
                ans.push_back(bools_to_ll(n_bools));
            }
        }
        else {
            //if significant bits match, then we can always do it (i think)
            //find first bit in which n differs from m. it's guaranteed that the n bit should be on
            //and m bit is off. 
            //then just use this bit to correct everything in m
            bool flag = false;
            vector<bool> op(63, false);
            for(int i = 0; i < op.size(); i++){
                if(!flag) {
                    if(n_bools[i] != m_bools[i]) {
                        flag = true;
                    }
                }
                if(flag) {
                    if(n_bools[i] != m_bools[i]) {
                        op[i] = true;
                    }
                }
            }
            n_bools = bools_xor(n_bools, op);
            ans.push_back(bools_to_ll(n_bools));
        }
        cout << ans.size() - 1 << "\n";
        for(int i = 0; i < ans.size(); i++){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
