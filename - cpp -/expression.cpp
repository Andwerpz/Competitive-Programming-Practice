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

struct var;
struct expr;
struct op;

struct var {
    char c;
    var() {}
    var(char _c) {c = _c;}
};

struct op {
    string type;
    expr l, r;
    op() {}
    op(string _type, expr _l, expr _r) {
        type = _type;
        l = _l;
        r = _r;
    }
};

struct expr {
    bool isvar = false;
    var v;
    op o;
    expr() {}
    expr(var _v) {v = _v, isvar = true;}
    expr(op _o) {o = _o, isvar = false;} 
};

var parse_var(string s);
expr parse_expr(string s);
op parse_op(string s);

var parse_var(string s) {
    return var(s[0]);
}

expr parse_expr(string s) {
    if(s[0] == '(') {
        return expr(parse_op(s.substr(1, s.size() - 2)));
    }
    else {
        return expr(parse_var(s));
    }
}

op parse_op(string s) {
    
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string s;
    getline(cin, s);
    expr e = parse_expr(s);
    
    return 0;
}