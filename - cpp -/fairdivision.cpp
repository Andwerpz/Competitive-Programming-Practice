#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2021 - C

//let's say that L is the amount of loot the first pirate will get after converging, and f is the fraction. 
//then the second pirate will get L(1 - f), and in general, the nth pirate will get L(1 - f)^(n - 1). 
//note that the total sum of loot must be equal to M. 

//we can factor out L, so that L(1 + (1 - f) + (1 - f)^2 + ... + (1 - f)^(n - 1)) = M. 
//solving for L gives us L = (1 * (1 - f)^n) / (1 - (1 - f)) * M
//note that since L and M have to be integers, the series also has to resolve to an integer. 

lll power(lll a, ll b) {
    lll ans = 1;
    for(int i = 0; i < b; i++) {
        ans *= a;
        if(ans > 1e30) {
            return -1;
        }
    }
    return ans;
}

string print(lll a) {
    string s = "";
    while(a != 0){
        ll dig = (ll) (a % 10);
        s.push_back((char) (dig + '0'));
        a /= (lll) 10;
    }
    reverse(s.begin(), s.end());
    return s;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, m; cin >> n >> m;
    if(n >= 70) {
        cout << "impossible\n";
        return 0;
    }
    ll ansp = -1, ansq = -1;
    for (ll q = 3980; q <= 3980 && (ansq == -1); ++q) {
        cout << "Q : " << q << "\n";
        for (ll p = 3977; p <= 3977; ++p) {
            cout << "TESTING : " << p << " " << q << "\n";
            lll a = q - p;
            lll b = q;
            lll a_n = power(a, n);
            lll b_n = power(b, n);
            cout << "a_n b_n " << print(a_n) << " " << print(b_n) << "\n";
            //cout << (ll) a_n << " " << (ll) b_n << "\n";
            if(a_n == -1 || b_n == -1) {
                continue;
            }
            lll top = b_n - a_n;
            lll bot = b_n - a * (b_n / b);
            cout << "bot top " << print(bot) << " " << print(top) << "\n";
            //cout << (ll) top << " " << (ll) bot << "\n";
            // cout << bot * m << "\n";
            lll tmp_m = m;
            cout << print(bot * 9994080458444214ll) << "\n";
            cout << print(bot * (lll) m) << "\n";
            cout << print(((bot * (lll) m) % top)) << "\n";
            
            // cout << m % (b_n / b) << "\n";
            if((bot * (lll) m) % top != 0){
                continue;
            }
            lll P = (bot * (lll) m) / top;
            cout << "P : " << (ll) P << "\n";
            if(P % (b_n / b) != 0){
                continue;
            }
            //cout << "FOUND ANS" << "\n";
            //cout << (ll) a_n << " " << (ll) b_n << "\n";
            ansp = p, ansq = q;
            break;
        }
    }
    
    if (ansp == -1) {
        cout << "impossible" << endl;
    } else {
        cout << ansp << " " << ansq << endl;
    }
    
    return 0;
}
