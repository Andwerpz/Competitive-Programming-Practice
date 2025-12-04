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

//AtCoder - ABC403F

//suppose that we remove the 
//factor := "(" <expr> ")" 
//rule from the grammar.

//then, it just becomes straightforwards dp, factors can only be numbers, then we do some backtracking dp on factors
//to figure out minimal terms, then some more dp on terms to figure out minimal expressions. 

//then, to solve the actual problem, we can just feed back the expressions into factors
//seems intimidating, but my intuition says that if we just do several rounds of relaxation, then the answer should
//pop right out. 

//some justification:
//observe that every time we inject expressions into terms, we have to always increase the expression length by 
//at least 2 due to the added parentheses. Since the minimum expression length for a given n is around log(n)
//(citation needed), this should only run for at most log(n) times. 

//experimentally, after the 5th iteration, everything is relaxed. 
//and if we raise N to 20000, after the 7th iteration, everything is relaxed. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    const int N = 20000;
    vector<string> factor(N + 1), term(N + 1), expr(N + 1);
    //base cases
    factor[1] = "1";
    factor[11] = "11";
    factor[111] = "111";
    factor[1111] = "1111";
    // 6767!!!
    // for(int i = 1; i <= N; i++) {
    //     string s = to_string(i);
    //     bool good = true;
    //     for(int j = 0; j < s.size(); j++) {
    //         if(s[j] != '6' && s[j] != '7') good = false;
    //     }
    //     if(good) factor[i] = s;
    // }
    //relax until no updates
    int itercnt = 0;
    while(true) {
        itercnt ++;
        cout << "ITER : " << itercnt << endl;
        bool done = true;
        //factor
        for(int i = 1; i <= N; i++) {
            if(expr[i].size() != 0 && (factor[i].size() == 0 || expr[i].size() + 2 < factor[i].size())) {
                factor[i] = "(" + expr[i] + ")";
                done = false;
            }
        }
        //term
        {
            vi dp(N + 1, 1e9), pv(N + 1, -1);
            for(int i = 1; i <= N; i++) {
                if(factor[i].size() != 0) {
                    if(term[i].size() == 0 || term[i].size() > factor[i].size()) {
                        term[i] = factor[i];
                        done = false;
                    }
                }
                if(term[i].size() == 0) continue;
                dp[i] = term[i].size();
            }
            for(int i = 0; i <= N; i++) {
                if(dp[i] == 1e9) continue;
                for(int j = 1; i * j <= N; j++) {
                    if(factor[j].size() == 0) continue;
                    if(dp[i] + factor[j].size() + 1 < dp[i * j]) {
                        dp[i * j] = dp[i] + factor[j].size();
                        pv[i * j] = i;
                    }
                }
                if(pv[i] != -1 && (term[i].size() == 0 || term[i].size() > dp[i])) {
                    term[i] = term[pv[i]] + "*" + factor[i / pv[i]];
                    done = false;
                }
            }
        }
        //expr
        {
            vi dp(N + 1, 1e9), pv(N + 1, -1);
            for(int i = 1; i <= N; i++) {
                if(term[i].size() != 0) {
                    if(expr[i].size() == 0 || expr[i].size() > term[i].size()) {
                        expr[i] = term[i];
                        done = false;
                    }
                }
                if(expr[i].size() == 0) continue;
                dp[i] = expr[i].size();
            }
            for(int i = 1; i <= N; i++) {
                if(dp[i] == 1e9) continue;
                for(int j = 1; i + j <= N; j++) {
                    if(term[j].size() == 0) continue;
                    if(dp[i] + term[j].size() + 1 < dp[i + j]) {
                        dp[i + j] = dp[i] + term[j].size();
                        pv[i + j] = i;
                    }
                }
                if(pv[i] != -1 && (expr[i].size() == 0 || expr[i].size() > dp[i])) {
                    expr[i] = expr[pv[i]] + "+" + term[i - pv[i]];
                    cout << "EXPR : " << expr[i] << " " << i << endl;
                    done = false;
                } 
            }
        }
        if(done) break;
    }
    cout << "ITERS : " << itercnt << "\n";

    // for(int i = 1; i <= N; i++) cout << i << " : " << expr[i] << endl;

    int n;
    cin >> n;
    cout << expr[n] << "\n";
    
    return 0;
}