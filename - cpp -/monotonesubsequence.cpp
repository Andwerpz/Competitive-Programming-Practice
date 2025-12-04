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

//Codeforces - 2152E

//guessforces, no idea why this works. 

bool debug = false;
vi jp;
int n;

vi interact(vi& a) {
    assert(a.size() >= 1);
    for(int i = 0; i < a.size(); i++) {
        assert(0 <= a[i] && a[i] < n * n + 1);
        if(i != 0) assert(a[i] > a[i - 1]);
    }

    cout << "? " << a.size() << " ";
    for(int i = 0; i < a.size(); i++) {
        cout << (a[i] + 1);
        if(i != a.size() - 1) cout << " ";
    }
    cout << endl;
    vi ans;
    if(debug) {
        // cout << "HERE" << endl;
        int p = a[0];
        ans.push_back(a[0]);
        for(int i = 1; i < a.size(); i++) {
            if(jp[a[i]] > jp[p]) {
                p = a[i];
                ans.push_back(a[i]);
            }
        }
        // cout << "HERE" << endl;
    }
    else {
        int c;
        cin >> c;
        for(int i = 0; i < c; i++) {
            int x;
            cin >> x;
            x --;
            ans.push_back(x);
        }
    }
    // cout << "DONE INTERACT : ";
    // for(int i = 0; i < ans.size(); i++) cout << ans[i] << " ";
    // cout << endl;
    return ans;
}

void report_ans(vi& a) {
    assert(a.size() == n + 1);
    for(int i = 0; i < a.size(); i++) {
        assert(0 <= a[i] && a[i] < n * n + 1);
        if(i != 0) assert(a[i] > a[i - 1]);
    }

    if(debug) {
        for(int i = 0; i < a.size(); i++) cout << jp[a[i]] << " ";
        cout << endl;

        bool is_inc = true, is_dec = true;
        for(int i = 1; i < a.size(); i++) {
            is_inc &= jp[a[i]] > jp[a[i - 1]];
            is_dec &= jp[a[i]] < jp[a[i - 1]];
        }
        assert(is_inc || is_dec);
    }

    cout << "! ";
    for(int i = 0; i < a.size(); i++) {
        cout << (a[i] + 1);
        if(i != a.size() - 1) cout << " ";
    }
    cout << endl;
}

void solve() {
    if(debug) {
        jp = vi(n * n + 1);
        for(int i = 0; i < n * n + 1; i++) jp[i] = i;
        random_shuffle(jp.begin(), jp.end());
    }

    int N = n * n + 1;
    vvi c(N);   //lower -> higher
    vvi rc(N);  //higher -> lower
    vb v(N, false);
    for(int i = 0; i < n; i++) {
        vi q;
        for(int j = 0; j < N; j++) {
            if(!v[j]) q.push_back(j);
        }
        if(q.size() == 0) continue;
        vi a = interact(q);
        // cout << "DONE GET ANS" << endl;
        assert(a.size() != 0);
        a.push_back(N);
        for(int j = 0; j < a.size() - 1; j++) {
            // cout << "a[j] : " << a[j] << " " << a[j + 1] << endl;
            if(a[j + 1] < N) {
                c[a[j]].push_back(a[j + 1]);
                rc[a[j + 1]].push_back(a[j]);
            }
            for(int k = a[j] + 1; k < a[j + 1]; k++) {
                if(!v[k]) {
                    c[k].push_back(a[j]);
                    rc[a[j]].push_back(k);
                }
            }
        }
        for(int j = 0; j < a.size(); j++) v[a[j]] = true;
        // cout << "DONE UPD GRAPH" << endl;
    }
    vi val(N, -1);
    vi indeg(N, 0);
    for(int i = 0; i < N; i++) {
        for(int x : c[i]) indeg[x] ++;
    }
    queue<int> q;
    for(int i = 0; i < N; i++) if(indeg[i] == 0) q.push(i), val[i] = 0;
    while(q.size()) {
        int cur = q.front();
        q.pop();
        // cout << "CUR : " << cur << "\n";
        for(int x : c[cur]) {
            indeg[x] --;
            if(indeg[x] == 0) q.push(x);
            val[x] = max(val[x], val[cur] + 1);
        }
    }

    // for(int i = 0; i < N; i++) cout << jp[i] << " ";
    // cout << endl;

    // for(int i = 0; i < N; i++) cout << val[i] << " ";
    // cout << endl;    

    vi lis, lds;
    {
        vi dp(N, 1);
        vi pv(N, -1);
        int mx = 0, mxind = -1;
        for(int i = 0; i < N; i++) {
            for(int x : c[i]) if(x > i) if(dp[i] + 1 > dp[x]) {
                dp[x] = dp[i] + 1;
                pv[x] = i;
            }
            if(dp[i] > mx) {
                mx = dp[i];
                mxind = i;
            }
        }
        assert(mxind != -1);
        int ptr = mxind;
        while(ptr != -1) {
            lis.push_back(ptr);
            ptr = pv[ptr];
        }
        reverse(lis.begin(), lis.end());
    }
    {
        vi dp(N, 1);
        vi pv(N, -1);
        int mx = 0, mxind = -1;
        for(int i = 0; i < N; i++) {
            for(int x : rc[i]) if(x > i) if(dp[i] + 1 > dp[x]) {
                dp[x] = dp[i] + 1;
                pv[x] = i;
            }
            if(dp[i] > mx) {
                mx = dp[i];
                mxind = i;
            }
        }
        assert(mxind != -1);
        int ptr = mxind;
        while(ptr != -1) {
            lds.push_back(ptr);
            ptr = pv[ptr];
        }
        reverse(lds.begin(), lds.end());
    }

    vi ans = lis;
    if(ans.size() < n + 1) ans = lds;
    assert(ans.size() >= n + 1);
    while(ans.size() > n + 1) ans.pop_back();

    // cout << "VALS : ";
    // for(int i = 0; i < ans.size(); i++) cout << val[ans[i]] << " ";
    // cout << endl;

    report_ans(ans);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    if(debug) {
        n = 5;
        while(true) {
            solve();
        }
    }
    else {
        int t;
        cin >> t;
        while(t--) {
            cin >> n;
            solve();
        }
    }
    
    
    return 0;
}