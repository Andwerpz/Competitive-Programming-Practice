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

//ICPC NERC 2025-2026 - D

//first, observe that there always exists an optimal solution in which the open segment is contiguous. 
//proof : suppose we have some optimal solution in which the open segment is not contiguous. 
//we can always transform the noncontiguous segments into one big contiguous segment of same size 
//by just moving the doors around. (W proof)

//ok, this means that for each layer, we don't care about the states where the open segment is discontiguous,
//which massively narrows down the amount of states we have to worry about. 
//specifically if a layer has L doors, then we only care about L + 1 states of these doors. 

//instead of thinking about moving doors around, we can think for each layer, we just have one open segment
//that we have L + 1 fixed positions that we can place it. 

//from here, lets think about binary searching for the answer. Given some length X, how can we check if 
//there is some placement of the N open segments from each layer somehow overlapping by some length X?
//actually, we can do this using some sweepline strategy in O(n * log(n)). 

bool is_valid(int n, vi& x1, vi& x2, vvi& l, vi& gs, int val) {
    // cout << "CHECK VALID : " << val << endl;
    vector<pii> ev; // {x, inc}
    for(int i = 0; i < n; i++) {
        assert(val <= gs[i]);
        ev.push_back({x1[i], 1});
        int pvr = x1[i] + (gs[i] - val) + 1;
        int xptr = x1[i];
        for(int j = 0; j < l[i].size(); j++) {
            int len = l[i][j];
            xptr += len;
            int cl = xptr;
            int cr = xptr + (gs[i] - val) + 1;
            if(cl > pvr) {
                ev.push_back({pvr, -1});
                ev.push_back({cl, 1});
            }
            pvr = cr;
        }
        ev.push_back({pvr, -1});
    }
    sort(ev.begin(), ev.end());
    int cnt = 0;
    for(int i = 0; i < ev.size(); ) {
        int cx = ev[i].first;
        int r = i;
        while(r != ev.size() && ev[r].first == cx) {
            // cout << "EV : " << cx << " " << ev[r].second << "\n";
            cnt += ev[r].second;
            r ++;
        }
        assert(cnt >= 0);
        if(cnt == n) return true;
        i = r;
    }
    return false;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vi x1(n), x2(n);
    vvi l(n);
    for(int i = 0; i < n; i++) {
        int k;
        cin >> k >> x1[i] >> x2[i];
        for(int j = 0; j < k; j++) {
            int x;
            cin >> x;
            l[i].push_back(x);
        }
    }
    int low = 1, high = 1e9 + 100;
    vi gs(n);
    for(int i = 0; i < n; i++) {
        gs[i] = x2[i] - x1[i];
        for(int x : l[i]) gs[i] -= x;
        high = min(high, gs[i]);
    }
    int ans = 0;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(is_valid(n, x1, x2, l, gs, mid)) {
            low = mid + 1;
            ans = mid;
        }
        else {
            high = mid - 1;
        }
    }
    cout << ans << "\n";
    
    return 0;
}