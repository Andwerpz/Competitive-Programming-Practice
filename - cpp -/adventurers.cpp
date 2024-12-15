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

//Codeforces - 2046C

//we can binary search over the answer. 

//to check if an answer k is valid, we do sweepline over y. Maintain two frequency arrays, one for above and one
//for below the line. Also, maintain the intervals on the frequency arrays on which min(left, right) >= k.
//then, for any y value, just need to see if the intervals on the above and bottom frequency arrays 
//are intersecting.

bool is_valid(vector<pii>& a, int val, pii& outpt) {
    int n = a.size();
    vi fa(n, 0), fb(n, 0);
    for(int i = 0; i < n; i++){
        fa[a[i].first] ++;
    }
    int apfx = 0, asfx = n;
    int bpfx = n, bsfx = 0;
    int apfxsum = 0, asfxsum = 0;
    int bpfxsum = 0, bsfxsum = 0;
    for(int i = 0; i < n;){
        int cy = a[i].second;
        while(i != n && a[i].second == cy) {
            int cx = a[i].first;
            fa[cx] --;
            fb[cx] ++;
            if(cx < apfx) apfxsum --;
            if(cx >= asfx) asfxsum --;
            if(cx < bpfx) bpfxsum ++;
            if(cx >= bsfx) bsfxsum ++;
            i++;
        }
        while(apfx != n && apfxsum < val) apfxsum += fa[apfx ++];
        while(asfx != 0 && asfxsum < val) asfxsum += fa[-- asfx];
        while(bpfx != 0 && bpfxsum - fb[bpfx - 1] >= val) bpfxsum -= fb[-- bpfx];
        while(bsfx != n && bsfxsum - fb[bsfx] >= val) bsfxsum -= fb[bsfx ++];
        if(min({apfxsum, asfxsum, bpfxsum, bsfxsum}) < val) continue;
        if(apfx > asfx || bpfx > bsfx) continue;
        //see if there is overlap
        int l = max(apfx, bpfx), r = min(asfx, bsfx);
        if(l <= r) {
            outpt = {l, cy + 1};
            return true;
        }
    }
    return false;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<pii> a(n);
        map<int, int> xmp, ymp, xrmp, yrmp;
        for(int i = 0; i < n; i++){
            cin >> a[i].first >> a[i].second;
        }
        {
            set<int> xs, ys;
            for(int i = 0; i < n; i++){
                xs.insert(a[i].first);
                ys.insert(a[i].second);
            }
            vi x, y;
            for(auto tmp : xs){
                x.push_back(tmp);
            }
            for(auto tmp : ys){
                y.push_back(tmp);
            }
            for(int i = 0; i < x.size(); i++) {
                xmp[x[i]] = i;
                xrmp[i] = x[i];
            }
            for(int i = 0; i < y.size(); i++){
                ymp[y[i]] = i;
                yrmp[i] = y[i];
            }
            for(int i = 0; i < n; i++){
                a[i].first = xmp[a[i].first];
                a[i].second = ymp[a[i].second];
            }
        }
        sort(a.begin(), a.end(), [](pii a, pii b) -> bool {
            return a.second < b.second;
        });
        int ansv = 0;
        pii anspt = {0, 0};
        int low = 1;
        int high = n;
        while(low <= high){
            int mid = low + (high - low) / 2;
            pii tmp;
            if(is_valid(a, mid, tmp)) {
                ansv = mid;
                anspt = tmp;
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
        anspt.first = xrmp[anspt.first];
        anspt.second = yrmp[anspt.second];
        cout << ansv << "\n";
        cout << anspt.first << " " << anspt.second << "\n";
    }
    
    return 0;
}