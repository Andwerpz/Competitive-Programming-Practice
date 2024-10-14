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

//Codeforces - 2003 E1 E2

//although dp is probably more straightforwards to implement, I use a constructive approach here. 

//consider the easy version first. We can partition all the elements of the array into two sets A and B, where
//max(A) < min(B). Naturally, in a segment, all elements that belong to A must be before all elements belonging
//to B, and in order to maximize inversions, we want to sort all occurrences of A in descending order, as well
//as occurrences of B. 

//I claim that the array with the most amount of inversions can be created with some process like this:
//pick some index 'cutoff'. Before cutoff, we will want to maximize the amount of occurrences of elements in B
//and after cutoff, maximize occurrences of A. The rationalization is that if you place elements of A
//after elements of B, you'll gain inversions, but not the other way around. 

//Given some cutoff, we can generate the associated array in O(n) time, and there are n cutoff points that we can 
//try, so there's our O(n^2) solution. This is sufficient for the easy version. 

//for the hard version, note that now the segments can be intersecting. This can just be reduced back to the easy 
//version by observing that if two segments are intersecting, then only the union acts as an actual segment
//where you can choose k. The xor of the segments on the other hand, are going to be fixed to A or B, depending on 
//if they are to the left or right of the intersection. 

//Note that now some combinations of segments are now impossible, when the intersection of a bunch of segments is the
//empty set. Since m is small, we can just brute force the intersections in m^2 time. 

int calc_ans(int n, vector<pii>& f_s, vector<pii>& f_l, vector<pii>& nf, int cutoff) {
    vb forced(n, false), is_large(n, false);
    for(int i = 0; i < f_s.size(); i++){
        for(int j = f_s[i].first; j != f_s[i].second; j++){
            forced[j] = true;
        }
    }
    for(int i = 0; i < f_l.size(); i++){
        for(int j = f_l[i].first; j != f_l[i].second; j++){
            forced[j] = true;
            is_large[j] = true;
        }
    }
    int ptr = 0;
    int lcnt = 0;
    int scnt = 0;
    int ans = 0;
    for(int i = 0; i < n; i++){
        if(!forced[i]) {
            while(ptr != nf.size() && nf[ptr].second <= i) {
                ptr ++;
            }
            if(i < cutoff) {
                if(ptr == nf.size() || nf[ptr].first != i){
                    is_large[i] = true;
                }
                else {
                    is_large[i] = false;
                }
            }
            else {
                if(ptr == nf.size() || nf[ptr].second - 1 != i){
                    is_large[i] = false;
                }
                else {
                    is_large[i] = true;
                }
            }
        }
        if(is_large[i]) {
            ans += lcnt;
            lcnt ++;
        }
        else {
            ans += lcnt + scnt;
            scnt ++;
        }
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<pii> seg(m);
        for(int i = 0; i < m; i++){
            cin >> seg[i].first >> seg[i].second;
            seg[i].first --;
        }
        //fix overlapping segments. Just do brute force m^2 search. 
        vvi c(m);
        for(int i = 0; i < m; i++){
            for(int j = i + 1; j < m; j++){
                int la = seg[i].first;
                int lb = seg[j].first;
                int ra = seg[i].second;
                int rb = seg[j].second;
                if(max(la, lb) < min(ra, rb)) {
                    c[i].push_back(j);
                    c[j].push_back(i);
                }
            }
        }
        //do clique search
        vvi g(0);
        {
            vi v(m, false);
            for(int i = 0; i < m; i++){
                if(v[i]) {
                    continue;
                }
                queue<int> q;
                q.push(i);
                v[i] = true;
                vi cg(0);
                while(q.size() != 0){
                    int cur = q.front();
                    q.pop();
                    cg.push_back(cur);
                    for(int j = 0; j < c[cur].size(); j++){
                        int next = c[cur][j];
                        if(!v[next]){
                            v[next] = true;
                            q.push(next);
                        }
                    }
                }
                g.push_back(cg);
            }
        }
        bool is_valid = true;
        //for each component, find the minimum and max l and r bounds
        vector<pii> f_s, f_l, nf; 
        for(int i = 0; i < g.size(); i++){
            int minl = n;
            int maxl = -1;
            int minr = n;
            int maxr = -1;
            for(int j = 0; j < g[i].size(); j++){
                int cur = g[i][j];
                minl = min(minl, seg[cur].first);
                maxl = max(maxl, seg[cur].first);
                minr = min(minr, seg[cur].second);
                maxr = max(maxr, seg[cur].second);
            }
            if(minr - maxl < 2) {
                is_valid = false;
            }
            f_s.push_back({minl, maxl});
            nf.push_back({maxl, minr});
            f_l.push_back({minr, maxr});
        }
        sort(nf.begin(), nf.end());
        if(!is_valid){  //bad component
            cout << "-1\n";
            continue;
        }
        int best_cutoff = -1;
        int best_ans = -1;
        //decide where to cutoff the large elements. 
        for(int i = 0; i <= n; i++){
            int cans = calc_ans(n, f_s, f_l, nf, i);
            if(cans > best_ans) {
                best_cutoff = i;
                best_ans = cans;
            }
        }
        cout << best_ans << "\n";
    }
    
    return 0;
}