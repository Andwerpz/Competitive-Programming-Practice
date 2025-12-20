#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<bool> vb;

//ICPC ECNA 2025 - B

//first, implement a way to evaluate some andor tree
//then, observe that computing the cost to change the evaluation of the andor tree can just be done in one pass

string t;
vvi c(0);
vb isl(0);
vi l(0);
vb lval(0);

bool eval(int cur) {
    if(isl[cur]) return lval[cur];
    if((l[cur] % 2 == 0) ^ (t == "A")) {
        // OR
        for(int x : c[cur]) if(eval(x)) return 1;
        return 0;
    }
    else {
        // AND
        for(int x : c[cur]) if(!eval(x)) return 0;
        return 1;
    }
}

int setv(int cur, bool val) {
    if(isl[cur]) return lval[cur] != val;
    if((l[cur] % 2 == 0) ^ (t == "A")) {
        // OR
        if(val) {
            int ans = 1e9;
            for(int x : c[cur]) ans = min(ans, setv(x, 1));
            return ans;
        }
        else {
            int ans = 0;
            for(int x : c[cur]) ans += setv(x, 0);
            return ans;
        }
    }
    else {
        // AND
        if(val) {
            int ans = 0;
            for(int x : c[cur]) ans += setv(x, 1);
            return ans;
        }
        else {
            int ans = 1e9;
            for(int x : c[cur]) ans = min(ans, setv(x, 0));
            return ans;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int lcnt;
    cin >> lcnt;
    cin >> t;
    int n = 0;
    {
        int lamt = 1;
        vi pv;
        vi pvind;
        for(int i = 0; i < lcnt; i++) {
            int pptr = 0;
            int namt = 0;
            vi nx;
            vi nxind;
            for(int j = 0; j < lamt; j++) {
                string tok;
                cin >> tok;
                if(tok == "T") {
                    isl.push_back(1);
                    lval.push_back(1);
                }
                else if(tok == "F") {
                    isl.push_back(1);
                    lval.push_back(0);
                }
                else {
                    int x = stoi(tok);
                    namt += x;
                    nx.push_back(x);
                    nxind.push_back(n);
                    isl.push_back(0);
                    lval.push_back(0);
                }
                l.push_back(i);
                if(i != 0) {
                    if(pv[pptr] == 0) pptr ++;
                    assert(pptr < pv.size());
                    assert(pv[pptr]);
                    pv[pptr] --;
                    c[pvind[pptr]].push_back(n);
                }
                n ++;
                c.push_back({});
            }
            pv = nx;
            pvind = nxind;
            lamt = namt;
        }
    }
    int ans = setv(0, !eval(0));
    cout << ans << "\n";

    return 0;
}