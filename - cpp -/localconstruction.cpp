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

//Codeforces - 2103D

//we can construct the array starting from the first removed to the last removed elements. 

//have a range of unused elements, it will initially start at [1, n]. If you're considering an odd parity operation, then it should
//consume elements from the top of the range, otherwise it should consume from the bottom. 

//you also have to be careful about elements at the edges of the array. Since there is a maximum of log(n) operations, you can build
//each layer in linear time. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        vvi c(n);
        int m = 0;
        for(int i = 0; i < n; i++) m = max(m, a[i]);
        m ++;
        vvi ord(m);
        for(int i = 0; i < n; i++){
            if(a[i] == -1) ord[m - 1].push_back(i), a[i] = m;
            else ord[a[i] - 1].push_back(i);
        }
        vi ans(n, -1);
        int l = 1, r = n;
        for(int i = 0; i < m; i++){
            int amt = ord[i].size();
            int cl, cr;
            if(i % 2) cl = l, cr = cl + amt - 1, l += amt;
            else cr = r, cl = cr - amt + 1, r -= amt;
            vvi chunk(0);
            chunk.push_back({ord[i][0]});
            for(int j = 1; j < ord[i].size(); j++){
                bool is_same = true;
                for(int k = ord[i][j - 1] + 1; k < ord[i][j]; k++) {
                    if(a[k] - 1 > i) is_same = false;
                }
                if(!is_same) chunk.push_back({});
                chunk[chunk.size() - 1].push_back(ord[i][j]);
            }
            bool firstt = true;
            for(int j = 0; j < chunk[0][0]; j++) if(a[j] - 1 > i) firstt = false;
            if(i % 2) {
                //first chunk ascending, rest descending
                if(firstt) for(int x : chunk[0]) ans[x] = cl ++;
                for(int j = firstt? 1 : 0; j < chunk.size(); j++) for(int x : chunk[j]) ans[x] = cr --;
            }
            else {
                //first chunk descending, rest ascending
                if(firstt) for(int x : chunk[0]) ans[x] = cr --;
                for(int j = firstt? 1 : 0; j < chunk.size(); j++) for(int x : chunk[j]) ans[x] = cl ++;
            }
        }
        for(int i = 0; i < n; i++) cout << ans[i] << " ";
        cout << "\n";
    }
    
    return 0;
}