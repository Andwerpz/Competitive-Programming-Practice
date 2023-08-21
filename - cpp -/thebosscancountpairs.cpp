#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1830B

//first solution didn't run in time because the actual complexity was around n^2 due to an oversight. 
//this solution should run in around n * sqrt(n) * log(n). 

//lets choose a random pair, (i, j). If this pair is good, then min(a[i], a[j]) <= sqrt(2 * n) must hold. 

//if for every unique value, m, where m <= sqrt(2 * n), we can find all good pairs that satisfy
//m = min(a[i], a[j]) in linear time, then we can solve the problem in n * sqrt(n) time. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<pair<int, int>> a(n, {0, 0});
        for(int i = 0; i < n; i++){
            cin >> a[i].first;
        }
        for(int i = 0; i < n; i++){
            cin >> a[i].second;
        }
        sort(a.begin(), a.end());
        // for(int i = 0; i < n; i++){
        //     cout << i << " : " << a[i].first << " " << a[i].second << "\n";
        // }
        ll ans = 0;
        int ptr = 0;
        while(ptr != n) {
            int pf = a[ptr].first;
            if((ll) pf * (ll) pf > 2 * n) {
                break;
            }
            map<int, ll> m;
            while(ptr != n && a[ptr].first == pf){
                int next = a[ptr].second;
                int tgt = pf * pf - next;
                if(m.find(tgt) != m.end()) {
                    ans += m.find(tgt) -> second;
                }
                if(m.find(next) == m.end()){
                    m.insert({next, 0});
                }
                m.find(next) -> second ++;
                ptr ++;
            }
            //cout << "PTR : " << ptr << endl;
            int nptr = ptr;
            while(nptr != n) {
                int npf = a[nptr].first;
                if((ll) pf * (ll) npf > 2 * n){
                    break;
                }
                int mul = pf * npf;
                while(nptr != n && a[nptr].first == npf) {
                    int next = a[nptr].second;
                    int tgt = mul - next;
                    if(m.find(tgt) != m.end()) {
                        ans += m.find(tgt) -> second;
                    }
                    nptr ++;
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
