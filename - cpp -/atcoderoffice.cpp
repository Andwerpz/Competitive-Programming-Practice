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

//AtCoder - ABC365G

//first note that given some x, we can compute the answer for queries of type {x, i} for all i in O(m) time.  
//also note that we can compute some arbitrary query {a, b} in O(|t[a]| + |t[b]|) time, where t[a] and t[b]
//are the times when person a and b enter / exit the office. 

//if for every person i with |t[i]| > sqrt(n) we precompute their answers with every other person, then that 
//would take O(n * sqrt(n)) time, as there can only be sqrt(n) people with |t[i]| > sqrt(n). And for any query
//where |t[a]|, |t[b]| <= sqrt(n), we can just compute in O(|t[a]| + |t[b]|). This gives us an O(n * sqrt(n))
//complexity. 

int calc_pfx(vector<pair<int, pii>>& s, int val) {
    if(s.size() == 0 || val < s[0].first) {
        return 0;
    }
    int low = 0;
    int high = s.size() - 1;
    int ind = 0;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(s[mid].first <= val) {
            ind = max(ind, mid);
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    int ans = s[ind].second.second;
    ans += min(val, s[ind].second.first) - s[ind].first;
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int thresh = sqrt(2e5);
    // int thresh = 0;
    int n, m;
    cin >> n >> m;
    vector<pii> t_arr(m);
    vvi t(n, vi(0));
    for(int i = 0; i < m; i++){
        int ti, pi;
        cin >> ti >> pi;
        pi --;
        t_arr[i] = {ti, pi};
        t[pi].push_back(ti);
    }
    vvi pre_m(n);
    for(int i = 0; i < n; i++){
        if(t[i].size() <= thresh) {
            continue;
        }
        vi pfx(m, 0), cans(n, 0), prev(n, -1);
        bool active = false;
        for(int j = 0; j < m; j++){
            int cur = t_arr[j].second;
            if(j != 0){
                pfx[j] = pfx[j - 1];
            }
            if(active) {
                pfx[j] += t_arr[j].first - t_arr[j - 1].first;
            }
            if(cur == i) {
                active = !active;
            }
            if(prev[cur] == -1){
                prev[cur] = j;
            }
            else {
                cans[cur] += pfx[j] - pfx[prev[cur]];
                prev[cur] = -1;
            }
        }
        pre_m[i] = cans;
    }
    vector<vector<pair<int, pii>>> seg(n);
    for(int i = 0; i < n; i++){
        int sum = 0;
        for(int j = 0; j < t[i].size(); j += 2){
            int l = t[i][j];
            int r = t[i][j + 1];
            seg[i].push_back({l, {r, sum}});
            sum += r - l;
        }
    }
    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        int ans = 0;
        if(t[a].size() <= thresh && t[b].size() <= thresh) {
            for(auto j = seg[a].begin(); j != seg[a].end(); j++){
                int l = j->first;
                int r = j->second.first;
                ans += calc_pfx(seg[b], r) - calc_pfx(seg[b], l);
            }
        }
        else {
            // cout << "USE PRE" << endl;
            if(t[a].size() < t[b].size()){
                swap(a, b);
            }
            ans = pre_m[a][b];
        }
        cout << ans << "\n";
    }
    
    return 0;
}