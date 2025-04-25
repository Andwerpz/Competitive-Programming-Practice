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

//Codeforces - 2096E

//with these problems with operations, have to simplify, simplify, simplify. 

//Observe that the lower bound on the number of operations is ceil(inv / 2), where inv is the number of inversions
//in s. This is because one operation can at most undo 2 inversions

//Observe that if you have some substring 'BB', you can always move this to the front. If there is a 'P' to 
//the left, you can use one operation to transform 'PBB' to 'BBP'. If you have 'BBB', then it's as if 'BB' is
//already to the left without an operation. So we can remove 'BB' and 'PP' from the string using the most efficient
//operations possible. 

//what we're left with is an alternating string : 'BPBP...BPB'. Note that now, we have to do an 'inefficient' 
//operation that only removes one inversion, so 'BPBP' becomes 'BBPP', and then we can remove 'BB' and 'PP' like
//normal. This actually doesn't affect the rest of the string, so we'll have to keep doing inefficient operations
//until we can remove the entire string. 

//key takeaway is to try to reduce the string as much as possible using known 'efficient' operations before 
//trying to solve. I guess I also need to assume that the efficient operations don't force me into doing more
//inefficient operations later on, but it should be at least worth one WA to test. 

ll invcnt(string& s) {
    ll ans = 0;
    ll pcnt = 0;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == 'P') pcnt ++;
        else ans += pcnt;
    }
    return ans;
}

ll solve(int n, string& s) {
    //loc black bears
    vi a;
    vi id(n, -1);
    int pcnt = 0;
    for(int i = 0; i < n; i++){
        if(s[i] == 'P') pcnt ++;
        else id[i] = a.size(), a.push_back(pcnt);
    }
    int m = a.size();
    vl dp(m + 1, 1e18);
    dp[0] = 0;
    // cout << "M : " << m << "\n";
    for(int i = 0; i < m; i++){
        //take one bear
        dp[i + 1] = min(dp[i + 1], dp[i] + (a[i] + 1) / 2);
        //take two bears
        if(i + 1 != m) {
            dp[i + 2] = min(dp[i + 2], dp[i] + a[i] + (a[i + 1] - a[i] + 1) / 2);
        }
    }
    cout << "INVCNT : " << invcnt(s) << "\n";
    for(int i = 0; i <= m; i++) cout << dp[i] << " ";
    cout << "\n";
    return dp[m];
}

void test() {
    srand(time(0));
    int n = 7;
    int cnt = 0;
    while(true) {
        cnt ++;
        string s(n, ' ');
        for(int i = 0; i < n; i++) {
            s[i] = (rand() % 2? 'B' : 'P');
        }

        ll ansb = solve(n, s);
        reverse(s.begin(), s.end());
        for(int i = 0; i < n; i++) s[i] = s[i] == 'B'? 'P' : 'B';
        ll ansp = solve(n, s);
        ll inv = invcnt(s);
        if(ansb != ansp) {
            cout << "S : " << s << "\n";
            cout << ansb << " " << ansp << "\n";
            break;
        }
        // if((inv + 1) / 2 + 1 < min(ansb, ansp)) {
        //     reverse(s.begin(), s.end());
        //     for(int i = 0; i < n; i++) s[i] = s[i] == 'B'? 'P' : 'B';
        //     cout << "S : " << s << "\n";
        //     cout << ansb << " " << ansp << "\n";
        //     cout << "INV : " << inv << " " << (inv + 1) / 2 << "\n";
        //     break;
        // }
        if(cnt % 1000 == 0) cout << "CNT : " << cnt << "\n";
    }
}

ll apply(string& s) {
    stack<char> st;
    int n = s.size();
    ll ans = 0;
    int pcnt = 0, bcnt = 0;
    for(int i = 0; i < n; i++) bcnt += s[i] == 'B';
    for(int i = 0; i < n; i++){
        if(st.size() != 0 && s[i] == st.top()) {
            st.pop();
            if(s[i] == 'B') {
                // cout << "ANSINC : " << pcnt << "\n";
                ans += pcnt;
            }
            else {
                // cout << "ANSINC : " << bcnt << "\n";
                ans += bcnt, pcnt --;
            }
        }
        else {
            st.push(s[i]);
            pcnt += s[i] == 'P';
        }
        bcnt -= s[i] == 'B';
        // cout << "I : " << i << " " << pcnt << " " << bcnt << "\n";
    }
    n = st.size();
    s = "";
    for(int i = 0; i < n; i++) {
        s.push_back(st.top());
        st.pop();
    }
    reverse(s.begin(), s.end());
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;
        ll ans = 0;
        while(invcnt(s) != 0) {
            ans += apply(s);
            // cout << "S : " << s << "\n";
            n = s.size();
            for(int i = 0; i < n - 1;){
                if(s[i] == 'P' && s[i + 1] == 'B') {
                    // cout << "SWAP : " << i << "\n";
                    ans ++, swap(s[i], s[i + 1]);
                    i += 4;
                }
                else {
                    i ++;
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}