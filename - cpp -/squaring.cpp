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

//Codeforces - 1995C

//observe that in theory, this problem is very easy. Just have to go left to right and make the current element at least
//as large as the previous one. The problem is that the numbers get too big too quickly, and you'll overflow. 

//so instead of keeping track of the numbers themselves, we can keep track of the log_2 of those numbers. Now, squaring is
//simply multiplying by 2. Actually, the same problem is present here where the numbers get too big, so we'll keep
//track of the log_2(log_2) of the numbers, and now squaring is simply adding 1. 

//there is one edge case with the number 1, where squaring does nothing. Have to check that first. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        bool poss = true;
        bool seen_nonone = false;
        int last_one = -1;
        for(int i = 0; i < n; i++){
            if(a[i] == 1){
                if(seen_nonone){
                    poss = false;
                }
                last_one = i;
            }
            else {
                seen_nonone = true;
            }
        }
        if(!poss){
            cout << "-1\n";
            continue;
        }
        vd b(n);
        for(int i = 0; i < n; i++){
            b[i] = log2(log2((ld) a[i]));
        }
        ll ans = 0;
        ld epsilon = 1e-7;
        for(int i = last_one + 2; i < n; i++){
            ld diff = b[i - 1] - b[i];
            if(diff > 0){
                ll amt = ceil(diff - epsilon);
                ans += amt;
                b[i] += amt;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}