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

//Meta Hacker Cup 2025 Round 1 - B

//this solution is actually wrong lmao

/*
1
4 3
1 2 3 3
1 4 4
*/

//my sol gives 4, best you can do is 3

//seems like correct solution is to just simulate this?

bool is_valid(vl& a, vl& b, int val) {
    ll sum = 0;
    ll req = 0;
    for(int i = 0; i < val; i++) {
        sum += a[i];
        req += sum;
    }
    if(val > b.size()) return 0;
    for(int i = 0; i < b.size(); i++) {
        req -= min(b[i], sum);
    }
    return req <= 0;
}   

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    // ifstream in("defining_prizes_input.txt");
    // streambuf *cinbuf = cin.rdbuf(); //save old buf
    // cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    // ofstream out("--out--.txt");
    // streambuf *coutbuf = cout.rdbuf(); //save old buf
    // cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

    int t;
    cin >> t;
    int casi = 0;
    while(t--) {
        casi ++;
        int n, m;
        cin >> n >> m;
        vl a(n), b(m);
        for(int i = 0; i < n; i++) cin >> a[i];
        for(int i = 0; i < m; i++) cin >> b[i];
        sort(b.begin(), b.end());
        reverse(b.begin(), b.end());
        map<int, int> f;
        for(int i = 0; i < n; i++) f[a[i]] ++;
        vl vf(0);
        for(auto i = f.begin(); i != f.end(); i++) {
            vf.push_back(i->second);
        }
        reverse(vf.begin(), vf.end());
        // cout << "VF : ";
        // for(int x : vf) cout << x << " ";
        // cout << "\n";
        int ans = 0;
        int low = 0, high = vf.size();
        while(low <= high) {
            int mid = low + (high - low) / 2;
            if(is_valid(vf, b, mid)) {
                low = mid + 1;
                ans = mid;
            }
            else {
                high = mid - 1;
            }
        }
        int aans = 0;
        // cout << "ANS : " << ans << "\n";
        for(int i = 0; i < ans; i++) aans += vf[i];
        cout << "Case #" << casi << ": " << aans << "\n";
    }
    
    return 0;
}