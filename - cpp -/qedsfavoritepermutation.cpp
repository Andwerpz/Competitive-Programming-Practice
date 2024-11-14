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

//Codeforces - 2030D

//every segment of 'RRRR...LLLL' is a segment that can be permuted arbitrarily, and thus sorted. 
//therefore, we just have to determine if there are some segments of the permutation that need to be
//sorted, but cross over a LR segment. 

//can maintain how many crosses happen. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, q;
        cin >> n >> q;
        vi a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            a[i] --;
        }
        string s;
        cin >> s;
        vi g(n, -1);
        vector<pii> seg(0);
        for(int i = 0; i < n; i++){
            int l = min(i, a[i]);
            int r = max(i, a[i]) + 1;
            seg.push_back({l, r});
        }
        sort(seg.begin(), seg.end());
        for(int i = 0; i < seg.size();){
            int l = seg[i].first;
            int r = seg[i].second;
            int rptr = i + 1;
            while(rptr != seg.size() && seg[rptr].first < r) {
                r = max(r, seg[rptr].second);
                rptr ++;
            }
            i = rptr;
            for(int j = l; j < r; j++){
                g[j] = i;
            }
        }
        // for(int i = 0; i < n; i++){
        //     cout << g[i] << " ";
        // }
        // cout << "\n";
        int bcnt = 0;
        for(int i = 0; i < n; i++){
            if(s[i] == 'L'){
                bcnt += i != n - 1 && s[i + 1] == 'R' && g[i] == g[i + 1];
            }
            // cout << "I : " << bcnt << "\n";
        }
        // cout << "INIT BCNT : " << bcnt << "\n";
        for(int i = 0; i < q; i++){
            int x;
            cin >> x;
            x --;
            if(s[x] == 'L'){
                bcnt -= x != n - 1 && s[x + 1] == 'R' && g[x] == g[x + 1];
            }
            else {
                bcnt -= x != 0 && s[x - 1] == 'L' && g[x] == g[x - 1];
            }
            s[x] = s[x] == 'L'? 'R' : 'L';
            if(s[x] == 'L'){
                bcnt += x != n - 1 && s[x + 1] == 'R' && g[x] == g[x + 1];
            }
            else {
                bcnt += x != 0 && s[x - 1] == 'L' && g[x] == g[x - 1];
            }
            // cout << "BCNT : " << bcnt << "\n";
            cout << (bcnt == 0? "YES" : "NO") << "\n";
        }
    }
    
    return 0;
}