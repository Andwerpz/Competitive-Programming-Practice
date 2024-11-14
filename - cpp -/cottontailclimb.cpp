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

//Meta Hacker Cup 2024 Round 2 - A1 A2

//for both, we can simply precompute all the valid mountains, and just do a linear scan to see
//what mountains are valid. 

//for A1, there are less than 100 or so, for A2, there are around 75 million. 

//ig there is also a meet in the middle solution, where you only consider the two mountain halves. 
//there are maybe around 10k mountain halves, so this is much more doable. 

void gen_inclist(vector<string>& ans, string& cur, int n) {
    if(cur.size() == n){
        ans.push_back(cur);
        return;
    }
    char start = '1';
    if(cur.size() != 0){
        start = cur[cur.size() - 1];
    }
    for(char i = start; i <= '8'; i++){
        cur.push_back(i);
        gen_inclist(ans, cur, n);
        cur.pop_back();
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ifstream in("--in--.txt");
    streambuf *cinbuf = cin.rdbuf(); //save old buf
    cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    ofstream out("--out--.txt");
    streambuf *coutbuf = cout.rdbuf(); //save old buf
    cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

    // cout << "SANITY" << endl;
    vl mlist(0);
    for(int i = 1; i <= 9; i++){
        mlist.push_back(i);
    }
    for(int k = 1; k <= 8; k++){
        string cur = "";
        vector<string> a(0);
        gen_inclist(a, cur, k);
        // cout << "DONE GEN INCLIST" << endl;
        for(int i = 0; i < a.size(); i++){
            for(int j = 0; j < a.size(); j++){
                string f = a[i];
                string s = a[j];
                reverse(s.begin(), s.end());
                char start = max(*f.rbegin(), *s.begin());
                for(char c = start + 1; c <= '9'; c++){
                    // cout << "TRY : " << f + string(1, c) + s << endl;
                    mlist.push_back(stoll(f + string(1, c) + s));
                }
            }
        }
    }
    // cout << "DONE GENERATING : " << mlist.size() << "\n";
    // for(int i = 0; i < mlist.size(); i++){
    //     cout << mlist[i] << "\n";
    // }

    vl pow10(18);
    pow10[0] = 1;
    for(int i = 1; i < pow10.size(); i++){
        pow10[i] = pow10[i - 1] * 10;
    }
    int t;
    cin >> t;
    int casi = 0;
    while(t--){
        casi ++;
        ll a, b, m;
        cin >> a >> b >> m;
        int ans = 0;
        for(int i = 0; i < mlist.size(); i++){
            if(mlist[i] < a || b < mlist[i]) {
                continue;
            }
            ans += (mlist[i] % m) == 0;
        }
        // for(int k = 0; k <= 8; k++){
        //     for(int i = 1; i + k <= 9; i++){
        //         ll val = (i + k) * pow10[k];
        //         for(int j = 0; j < k; j++){
        //             val += (i + j) * (pow10[j] + pow10[2 * k - j]);
        //         }
        //         // cout << "TEST VAL" << val << "\n";
        //         if(val % m == 0 && a <= val && val <= b){
        //             ans ++;
        //         }
        //     }
        // }
        cout << "Case #" << casi << ": " << ans << "\n";
    }
    
    return 0;
}