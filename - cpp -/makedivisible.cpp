#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ARC150B

//first consider a brute force solution; we increment a, and for each a, we figure out the 
//minimum y where (b + y) % a == 0. 

//then, we notice that sometimes when a increases, y also increases, and other times it will
//decrease. When will y decrease? It will decrease when the value of (b / a) decreases. 

//thus, we need to find all points where (b / a) decreases, and test all of them. We can find
//each one in log(b) time, and there are around sqrt(b) of them in total. 

//we also need to make sure to test all the divisors of b. 

vector<int> lp; //lowest prime factor 
vector<int> pr; //prime list

void prime_sieve(int n) {
    lp = vector<int>(n + 1);
    pr = vector<int>(0);
    for(int i = 2; i <= n; i++) {
        if(lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; i * pr[j] <= n; j++) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }
}

vector<int> find_prime_factors(int val) {
    vector<int> factors(0);
    for(int i = 0; i < pr.size(); i++){
        while(val % pr[i] == 0){
            factors.push_back(pr[i]);
            val /= pr[i];
        }
    }
    if(val != 1){
        factors.push_back(val);
    }
    return factors;
}

void find_divisors_helper(vector<int>& p, vector<int>& c, int ind, int val, vector<int>& ans) {
    if(ind == p.size()) {
        ans.push_back(val);
        return;
    }
    for(int i = 0; i <= c[ind]; i++){
        find_divisors_helper(p, c, ind + 1, val, ans);
        val *= p[ind];
    }
}

vector<int> find_divisors(int val) {
    vector<int> factors = find_prime_factors(val);
    map<int, int> m;
    vector<int> p(0);
    vector<int> c(0);
    for(int i = 0; i < factors.size(); i++){
        int next = factors[i];
        if(m.find(next) == m.end()) {
            p.push_back(next);
            c.push_back(0);
            m.insert({next, m.size()});
        }
        int ind = m[next];
        c[ind] ++;
    }
    vector<int> div(0);
    find_divisors_helper(p, c, 0, 1, div);
    return div;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    prime_sieve(1e6);
    while(t--){
        ll a, b;
        cin >> a >> b;
        ll ans = (a - (b % a)) % a;
        vector<int> div = find_divisors(b);
        for(int i = 0; i < div.size(); i++){
            ll d = div[i];
            if(d < a) {
                continue;
            }
            ll x = d - a;
            ll y = (d - (b % d)) % d;
            ans = min(ans, x + y);
            //cout << "TRY : " << x << " " << y << "\n";
        }
        ll x = 0;
        while(a < b) {
            //find the next a where the value of b / a decreases. 
            ll cur = b / a;
            ll low = a + 1;
            ll high = 1e9;
            ll next = high;
            while(low <= high) {
                ll mid = low + (high - low) / 2;
                if(b / mid < cur) {
                    next = min(next, mid);
                    high = mid - 1;
                }
                else {
                    low = mid + 1;
                }
            }
            x += next - a;
            a = next;
            ll y = (a - (b % a)) % a;
            // if(x + y < ans) {
            //     cout << "X : " << x << " Y : " << y << "\n";
            // }
            ans = min(ans, (a - (b % a)) % a + x);
            //cout << "NEXT : " << next << "\n";
        }
        cout << ans << "\n";
    }
    
    return 0;
}
