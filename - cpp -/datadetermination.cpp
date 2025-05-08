#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<ll> vl;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

//3rd Universal Cup, Stage 7: Warsaw - D

//implementation. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int t;
    cin >> t;
    while(t--){
        int n, k, m;
        cin >> n >> k >> m;
        vi a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        bool is_valid = false;
        sort(a.begin(), a.end());
        if(k % 2 == 0){
            map<int, int> eocc, locc;
            for(int i = 0; i < n; i++) locc[a[i]] = i;
            for(int i = n - 1; i >= 0; i--) eocc[a[i]] = i;
            set<int> s;
            for(int i = 0; i < n; i++) s.insert(a[i]);
            int ptr = m;
            while(s.lower_bound(ptr) != s.end()) {
                int nxt = *(s.lower_bound(ptr));
                ptr = nxt + 1;
                if(nxt == m) {
                    int mcnt = locc[m] - eocc[m] + 1;
                    if(mcnt < 2) continue;
                    mcnt -= 2;
                    int pcnt = eocc[m], scnt = n - locc[m] - 1;
                    int diff = max(0, k / 2 - 1 - pcnt) + max(0, k / 2 - 1 - scnt);
                    if(diff > mcnt) continue;
                    is_valid = true;
                }
                else {
                    int low = m - (nxt - m), high = nxt;
                    if(!s.count(low) || !s.count(high)) continue;
                    int lcnt = locc[low], hcnt = n - eocc[high] - 1;
                    // cout << "NXT : " << nxt << " " << lcnt << " " << hcnt << "\n";
                    if(lcnt >= k / 2 - 1 && hcnt >= k / 2 - 1) is_valid = true;
                }
            }
        }
        else {
            int pcnt = 0, scnt = n;
            for(int i = 0; i < n; i++){
                scnt --;
                if(pcnt >= k / 2 && scnt >= k / 2 && a[i] == m) is_valid = true;
                pcnt ++;
            }
        }
        cout << (is_valid? "TAK" : "NIE") << "\n";
    }

    return 0;
}