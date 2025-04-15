#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

//The 3rd Universal Cup. Stage 18: Southeastern Europe - F

//kinda graph, kinda dp??

//the problem statement is confusing. What it's actually asking is remove the maximum amount of magical items such that every
//pair that is good before removing stays good after removing. 

//Observe that we can safely remove from every bag all the elements that are not the min or max, as two bags are good iff the
//ranges defined by their min and max intersect in some way. This puts an upper bound on the answer, 2n. 

//Now, we just want to see the maximum amount of bags we can lower from 2 to 1 element. First, when can we turn a bag from 2 to
//1 elements? There must exist a element in the bag such that it is within all the ranges defined by the bags that it is 
//originally intersecting. We can test this quickly using some segment trees. 

//then, observe that if we turn some bag from 2 to 1, we can't turn any of the bags it is touching from 2 to 1. To maximize
//the amount of bags we turn from 2 to 1, we can do some dp. 

struct TreeMin {
    typedef int T;
    static constexpr T unit = 1e9;
    T f(T a, T b) { return min(a, b);}
    vector<T> s; int n;
    TreeMin(int n = 0, T def = unit):s(n * 2, def), n(n) {}
    void update(int pos, T val) {
        for (s[pos += n] = val; pos /= 2;) {
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
        }
    }
    T query(int b, int e) {
        T ra = unit, rb = unit;
        for(b += n, e += n; b < e; b /= 2, e /= 2) {
            if(b % 2) ra = f(ra, s[b++]);
            if(e % 2) rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
};

struct TreeMax {
    typedef int T;
    static constexpr T unit = 0;
    T f(T a, T b) { return max(a, b);}
    vector<T> s; int n;
    TreeMax(int n = 0, T def = unit):s(n * 2, def), n(n) {}
    void update(int pos, T val) {
        for (s[pos += n] = val; pos /= 2;) {
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
        }
    }
    T query(int b, int e) {
        T ra = unit, rb = unit;
        for(b += n, e += n; b < e; b /= 2, e /= 2) {
            if(b % 2) ra = f(ra, s[b++]);
            if(e % 2) rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n;
    cin >> n;
    vector<vi> b(n);
    for(int i = 0; i < n; i++){
        int k;
        cin >> k;
        b[i] = vi(k);
        for(int j = 0; j < k; j++){
            cin >> b[i][j];
        }
    }
    int mxv = 0;
    {
        set<int> s;
        for(int i = 0; i < n; i++) for(int j = 0; j < b[i].size(); j++) s.insert(b[i][j]);
        map<int, int> m;
        int ptr = 0;
        for(auto i = s.begin(); i != s.end(); i++){
            m[*i] = ptr ++;
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < b[i].size(); j++) b[i][j] = m[b[i][j]];
        }
        mxv = ptr - 1;
    }
    vi mn(n, 1e9), mx(n, -1);
    for(int i = 0; i < n; i++) for(int j = 0; j < b[i].size(); j++) mn[i] = min(mn[i], b[i][j]), mx[i] = max(mx[i], b[i][j]);
    vector<pair<int, pii>> ev;
    for(int i = 0; i < n; i++){
        ev.push_back({mn[i], {mn[i], mx[i]}});
        ev.push_back({mx[i] + 1, {mn[i], mx[i]}});
    }
    sort(ev.begin(), ev.end());
    TreeMax lseg(mxv + 1, -1e9);
    TreeMin rseg(mxv + 1, 1e9);
    {
        set<int> ls, rs;
        int ptr = 0;
        for(int i = 0; i <= mxv; i++){
            // cout << "I : " << i << "\n";
            while(ptr != ev.size() && ev[ptr].first == i) {
                int u = ev[ptr].second.first, v = ev[ptr].second.second;
                ptr ++;
                // cout << "EV : " << u << " " << v << "\n";
                if(ls.count(u)) ls.erase(u), rs.erase(v);
                else ls.insert(u), rs.insert(v);
            }
            if(ls.size() != 0){
                lseg.update(i, *ls.rbegin()), rseg.update(i, *rs.begin());
            }
        }
    }
    // for(int i = 0; i <= mxv; i++) cout << lseg.query(i, i + 1) << " ";
    // cout << "\n";
    // for(int i = 0; i <= mxv; i++) cout << rseg.query(i, i + 1) << " ";
    // cout << "\n";
    vi dp(mxv + 2, 0);    
    vector<pii> ord(n);
    for(int i = 0; i < n; i++) ord[i] = {mx[i], i};
    sort(ord.begin(), ord.end());
    int ptr = 0;
    for(int i = 0; i <= mxv; i++){
        if(ptr == ord.size() || ord[ptr].first != i) {
            dp[i + 1] = max(dp[i], dp[i + 1]);
            continue;
        }
        int ind = ord[ptr ++].second;
        int l = mn[ind], r = mx[ind];
        int mxl = lseg.query(l, r + 1), mnr = rseg.query(l, r + 1);
        // cout << "L R : " << l << " " << r << " " << mxl << " " << mnr << "\n";
        bool can_col = false;
        for(int j = 0; j < b[ind].size(); j++){
            int next = b[ind][j];
            if(mxl <= next && next <= mnr) can_col = true;
        }
        if(can_col) {
            // cout << "CAN COL : " << ind << "\n";
            dp[i + 1] = max(dp[i + 1], dp[l] + 1);
        }
        dp[i + 1] = max(dp[i], dp[i + 1]);
    }
    // for(int i = 0; i < dp.size(); i++) cout << dp[i] << " ";
    // cout << "\n";
    int ans = 2 * n - dp[mxv + 1];
    cout << ans << "\n";

    return 0;
}