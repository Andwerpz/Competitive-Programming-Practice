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

//3rd Universal Cup Stage 31 : Wroclaw - E

//first, write a parser :D

//Observe that if all the variables are set to true, then the result must be true if we only use 'min' and '<='. 
//So if the output of the given expression is false when all the variables are set to true, then it's 
//impossible to make. 

//Otherwise it's always possible. Notice that if we assume that some variable is false, we can get False
//by taking the min of all variables. Then, we can rederive 'max' and '<':

//min(a, b) = a & b
//False = min(a, ..., j)
//a <= b = !a | b
//a <= False = !a
//max(a, b) = a | b = !(!a) | b = (a <= False) <= b
//a < b = !a & b = min(!a & b) = min((a <= False), b)

struct var;
struct expr;
struct op;

set<char> vs;
struct var {
    char c;
    var() {}
    var(char _c) {c = _c; vs.insert(_c);}
};

struct op {
    string type;
    expr *l, *r;
    op() {}
    op(string _type, expr *_l, expr *_r) {
        type = _type;
        l = _l;
        r = _r;
    }
};

struct expr {
    bool isvar = false;
    var *v;
    op *o;
    expr() {}
    expr(var *_v) {v = _v, isvar = true;}
    expr(op *_o) {o = _o, isvar = false;} 
};

var* parse_var(string& s, int& ptr);
expr* parse_expr(string& s, int& ptr);
op* parse_op(string& s, int& ptr);

var* parse_var(string& s, int& ptr) {
    return new var(s[ptr ++]);
}

expr* parse_expr(string& s, int& ptr) {
    // cout << "PARSE EXPR : " << ptr << endl;
    int el = ptr;
    expr* ans;
    if(s[ptr] == '(') { //(op)
        ptr ++;
        ans = new expr(parse_op(s, ptr));
        ptr ++;
    }
    else { //var
        ans = new expr(parse_var(s, ptr));
    }
    // cout << "DONE PARSE EXPR : " << ptr << " " << s.substr(el, ptr - el) << endl;
    return ans;
}

op* parse_op(string& s, int& ptr) {
    int el = ptr;
    expr *l, *r;
    string ty;
    if(s[ptr] == 'm') {
        //either min or max
        if(s[ptr + 1] == 'i') ty = "min";
        else ty = "max";
        ptr += 4;
        l = parse_expr(s, ptr);
        ptr ++;
        r = parse_expr(s, ptr);
    }
    else {
        //< or <=
        l = parse_expr(s, ptr);
        ptr ++;
        if(s[ptr + 1] == '=') ty = "<=", ptr ++;
        else ty = '<';
        ptr += 2;
        r = parse_expr(s, ptr);
    }
    // cout << "DONE PARSE OP : " << s.substr(el, ptr - el) << endl;
    return new op(ty, l, r);
}

expr* parse_expr(string s) {
    int ptr = 0;
    return parse_expr(s, ptr);
}

bool eval(expr *e, vb& val);
bool eval(op *o, vb& val);
bool eval(var *v, vb& val);

bool eval(expr *e, vb& val) {
    // cout << "EVAL EXPR" << endl;
    if(e->isvar) return eval(e->v, val);
    else return eval(e->o, val);
}

bool eval(op *o, vb& val) {
    // cout << "EVAL OP : " << o->type << endl;
    if(o->type == "min") {
        return min(eval(o->l, val), eval(o->r, val));
    }
    else if(o->type == "max") {
        return max(eval(o->l, val), eval(o->r, val));
    }
    else if(o->type == "<") {
        return eval(o->l, val) < eval(o->r, val);
    }
    else if(o->type == "<=") {
        return eval(o->l, val) <= eval(o->r, val);
    }
    else {
        cout << "UNRECOGNIZED TYPE D:" << endl;
    }
}

bool eval(var *v, vb& val){
    // cout << "EVAL VAR : " << v->c << " " << val[v->c - 'a'] << endl;
    return val[v->c - 'a'];
}

expr* solve(expr* e);
op* solve(op* o);
var* solve(var* v);

expr* solve(expr *e) {
    if(e->isvar) return new expr(solve(e->v));
    else return new expr(solve(e->o));
}

expr* gen_false() {
    if(vs.size() == 1) return new expr(new var(*vs.begin()));
    auto ptr = vs.begin();
    expr *ans = new expr(new op("min", new expr(new var(*ptr ++)), new expr(new var(*ptr ++))));
    for(int i = 2; i < vs.size(); i++){
        ans = new expr(new op("min", ans, new expr(new var(*ptr ++))));
    }
    return ans;
}

op* solve(op *o) {
    // cout << "SOLVE OP : " << o->type << endl;
    if(o->type == "min") {
        return new op("min", solve(o->l), solve(o->r));
    }
    else if(o->type == "max") {
        expr *inner = new expr(new op("<=", solve(o->l), gen_false()));
        return new op("<=", inner, solve(o->r));
    }
    else if(o->type == "<") {
        expr *inner = new expr(new op("<=", solve(o->l), gen_false()));
        return new op("min", inner, solve(o->r));
    }
    else if(o->type == "<=") {
        return new op("<=", solve(o->l), solve(o->r));
    }
    else {
        cout << "UNRECOGNIZED TYPE D:" << endl;
    }  
}

var* solve(var *v) {
    return new var(v->c);
}

void print(expr* e);
void print(op* o);
void print(var* v);

void print(expr* e) {
    if(e->isvar) print(e->v);
    else {
        cout << "(";
        print(e->o);
        cout << ")";
    }
}

void print(op* o){
    if(o->type == "min") {
        cout << "min ";
        print(o->l);
        cout << " ";
        print(o->r);
    }
    else if(o->type == "max") {
        cout << "max ";
        print(o->l);
        cout << " ";
        print(o->r);
    }
    else if(o->type == "<") {
        print(o->l);
        cout << " < ";
        print(o->r);
    }
    else if(o->type == "<=") {
        print(o->l);
        cout << " <= ";
        print(o->r);
    }
    else {
        cout << "UNRECOGNIZED TYPE D:" << endl;
    }
}

void print(var* v) {
    cout << v->c;
}

bool equiv(expr* a, expr* b) {
    for(int i = 0; i < (1 << 10); i++){
        vb val(10);
        for(int j = 0; j < 10; j++) val[j] = i & (1 << j);
        if(eval(a, val) != eval(b, val)) return false;
    }
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string s;
    getline(cin, s);
    expr *e = parse_expr(s);
    vb val(10, true);
    if(!eval(e, val)) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    expr *ans = solve(e);
    assert(equiv(e, ans));
    print(ans);
    
    return 0;
}