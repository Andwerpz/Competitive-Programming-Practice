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

//2025 ICPC Asia Chengdu Regional Contest - D

//big heuristics practice

//observe that the amount of states isn't that large: 200^2 * 22 * 2^6 * 2 * 3 ~= 3*10^8
//we can probably just get away with brute force + caching + heuristics

//i came up with two heuristics:

//first one is just seeing if it's impossible to get to the goal state due to insufficient balls or score. 
//just compute the maximum score you can get at the current state, as well as the minimum amount of balls needed to get
//to the target score. 

//second one is avoiding the players repeatedly alternating not sinking a ball. If we have three not sinks in a row, it's identical
//to just one not sink, so if the previous two moves were not sink, then you dont' have to consider not sinking the ball on this move. 

int A, B, N, P;
string ans;
set<ll> v;

ll encode(int a, int b, int nr, vb& sc, int p, int ph) {
    ll mult = 1;
    ll ans = 0;
    ans += a * mult;
    mult *= 201;
    ans += b * mult;
    mult *= 201;
    ans += nr * mult;
    mult *= 22;
    for(int i = 2; i <= 7; i++) {
        ans += sc[i] * mult;
        mult *= 2;
    }
    ans += p * mult;
    mult *= 2;
    ans += ph * mult;
    mult *= 3;
    return ans;
}

int dfscnt = 0;
bool dfs(int a, int b, int nr, vb& sc, int sccnt, int p, int ph) {
    if(a > A || b > B || nr + sccnt < N) {
        //impossible to reach goal state
        return false;
    }
    if(a == A && b == B && nr + sccnt == N && p == P) {
        //found goal state
        return true;
    }   
    ll enc = encode(a, b, nr, sc, p, ph);
    if(v.count(enc)) {
        return false;
    }
    v.insert(enc);

    dfscnt ++;

    //if there are no balls left, no actions can be taken
    if(nr + sccnt == 0) return false;

    //early out if the score can't reach, or we don't have enough balls to reach
    {
        int req = (A - a) + (B - b);
        int reqb = 0;
        if(ph == 1) req -= 7;
        for(int i = 0; i < nr; i++) {
            if(req <= 0) break;
            req -= 1;
            reqb ++;
            if(req <= 0) break;
            req -= 7;
        }
        for(int i = 7; i >= 2; i--) {
            if(!sc[i]) continue;
            if(req <= 0) break;
            req -= i;
            reqb ++;
        }
        // cout << "REQ : " << req << " " << reqb << "\n";
        if(req > 0) return false;
        if((nr + sccnt) - reqb < N) return false;
    }

    //simulate game
    if(p == 0) {
        if(ph == 0) {
            //if no red balls present, proceed to phase 3
            if(nr == 0) return dfs(a, b, nr, sc, sccnt, p, 2);
            //sink red ball
            {
                ans.push_back('1');
                bool stat = dfs(a + 1, b, nr - 1, sc, sccnt, p, 1);
                if(stat) return true;
                ans.pop_back();
            }
        }
        else if(ph == 1) {
            //there should be some colored balls 
            assert(sccnt != 0);
            //sink colored ball
            for(int i = 7; i >= 2; i--) {
                if(!sc[i]) continue;
                ans.push_back((char) '0' + i);
                bool stat = dfs(a + i, b, nr, sc, sccnt, p, 0);
                if(stat) return true;
                ans.pop_back();
            }
        }
        else if(ph == 2) {
            //there should be no red balls
            assert(nr == 0);
            //sink lowest value colored ball
            for(int i = 2; i <= 7; i++) {
                if(!sc[i]) continue;
                ans.push_back((char) '0' + i);
                sc[i] = false;
                bool stat = dfs(a + i, b, nr, sc, sccnt - 1, p, 2);
                if(stat) return true;
                sc[i] = true;
                ans.pop_back();
                break;
            }
        }
        else assert(false);
    }
    else {
        assert(p == 1);
        if(ph == 0) {
            //if no red balls present, proceed to phase 3
            if(nr == 0) return dfs(a, b, nr, sc, sccnt, p, 2);
            //sink red ball
            {
                ans.push_back('1');
                bool stat = dfs(a, b + 1, nr - 1, sc, sccnt, p, 1);
                if(stat) return true;
                ans.pop_back();
            }
        }
        else if(ph == 1) {
            //there should be some colored balls 
            assert(sccnt != 0);
            //sink colored ball
            for(int i = 7; i >= 2; i--) {
                if(!sc[i]) continue;
                ans.push_back((char) '0' + i);
                bool stat = dfs(a, b + i, nr, sc, sccnt, p, 0);
                if(stat) return true;
                ans.pop_back();
            }
        }
        else if(ph == 2) {
            //there should be no red balls
            assert(nr == 0);
            //sink lowest value colored ball
            for(int i = 2; i <= 7; i++) {
                if(!sc[i]) continue;
                ans.push_back((char) '0' + i);
                sc[i] = false;
                bool stat = dfs(a, b + i, nr, sc, sccnt - 1, p, 2);
                if(stat) return true;
                sc[i] = true;
                ans.pop_back();
                break;
            }
        }
        else assert(false);
    }
    //don't sink ball, make sure we haven't done nothing for two previous turns
    if(ans.size() < 2 || ans[ans.size() - 1] != '/' || ans[ans.size() - 2] != '/') {
        ans.push_back('/');
        bool stat = dfs(a, b, nr, sc, sccnt, p ^ 1, 0);
        if(stat) return true;
        ans.pop_back();
    }

    return false;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        cin >> A >> B >> N >> P;
        if(A + B > 147) {
            cout << "NA\n";
            continue;
        }
        v = set<ll>();
        ans = "";
        vb sc(8, true);
        bool stat = dfs(0, 0, 15, sc, 6, 0, 0);
        if(stat) cout << ans << "\n";
        else cout << "NA\n";
        // cout << "DFSCNT : " << dfscnt << "\n";
        dfscnt = 0;
    }

    // int mx_dfscnt = 0;
    // int found_cnt = 0;
    // for(int i = 0; i <= 147; i++) {
    //     cout << "I : " << i << endl;
    //     for(int j = 0; i + j <= 147; j++) {
    //         // cout << "I J : " << i << " " << j << " : " << found_cnt << endl;
    //         for(int n = 0; n <= 21; n++) {
    //             for(int p = 0; p <= 1; p++) {
    //                 A = i, B = j, N = n, P = p;
    //                 v.clear();
    //                 vb sc(8, true);
    //                 ans = "";
    //                 bool stat = dfs(0, 0, 15, sc, 6, 0, 0);
    //                 // if(stat) cout << ans << endl;
    //                 // else cout << "NA" << endl;
    //                 found_cnt += stat;
    //                 if(dfscnt > mx_dfscnt) {
    //                     cout << "MX : " << i << " " << j << " " << n << " " << p << " : " << dfscnt << " " << stat << "\n";
    //                     mx_dfscnt = max(dfscnt, mx_dfscnt);
    //                 }
    //                 dfscnt = 0;
    //             }
    //         }
    //     }
    // }
    
    
    return 0;
}