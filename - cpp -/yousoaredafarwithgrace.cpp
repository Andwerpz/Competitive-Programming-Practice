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

//Codeforces - 2084C

//Observe that each element in a is 'matched' to some other element in b. So if a[i] is matched to b[i],
//there has to be some j such that a[i] = b[j] and a[j] = b[i]. If this is not the case, then it's always
//impossible to make them mirrored. 

//otherwise, it's always possible. I'll leave impl details to the reader to figure out. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<pii> a(n);
        for(int i = 0; i < n; i++) cin >> a[i].first;
        for(int i = 0; i < n; i++) cin >> a[i].second;
        map<int, int> m;
        for(int i = 0; i < n; i++) m[a[i].first] = a[i].second;
        int scnt = 0;
        bool is_valid = true;
        for(int i = 0; i < n; i++){
            int bval = a[i].second;
            if(bval == a[i].first) {
                if(n % 2 == 0) is_valid = false;
                scnt ++;
                if(scnt > 1) is_valid = false;
            }
            if(m[bval] != a[i].first) is_valid = false;
        }
        if(n % 2 == 1 && scnt != 1) {
            is_valid = false;
        }
        if(!is_valid) {
            cout << "-1\n";
            continue;
        }
        map<pii, int> indmp;
        for(int i = 0; i < n; i++) indmp[a[i]] = i;
        int l = 0, r = n - 1;
        vector<pii> ans(0);
        set<pii> sorted;
        for(int i = 0; i < n; i++){
            if(a[i].first == a[i].second) continue;
            if(sorted.count(a[i])) continue;
            int aval = a[i].first, bval = a[i].second;
            int find = indmp[{aval, bval}], sind = indmp[{bval, aval}];
            if(find > sind) swap(find, sind);
            pii lp = a[l], rp = a[r];
            // cout << "LR FIND SIND : " << l << " " << r << " " << find << " " << sind << "\n";
            swap(a[l], a[find]), swap(a[r], a[sind]);
            if(l != find) ans.push_back({l, find});
            if(r != sind) ans.push_back({r, sind});
            indmp[lp] = find;
            indmp[rp] = sind;
            sorted.insert(a[l]), sorted.insert(a[r]);
            l ++, r --;
        }
        cout << ans.size() << "\n";
        for(int i = 0; i < ans.size(); i++) {
            cout << ans[i].first + 1 << " " << ans[i].second + 1 << "\n";
        }
    }
    
    return 0;
}