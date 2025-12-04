#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

typedef pair<int,int> pii;
typedef vector<int> vi;
#define rep(i, a ,b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(s) (int) (x).size()
typedef vector<vi> vvi;

//SWERC 2020 - H

/*


3
+0 +2
-0 +1 -2 -1

1
2
2

*/

struct P {
    P *l, *r;
    int val;
    P(P* l, P* r, int val): l(l), r(r), val(val) {}
    P(int val): l(nullptr), r(nullptr), val(val) {}
};

int n;
vector<P*> trees;

P* create(int l, int r) {
    if(l + 1 == r) {
        return new P(0);
    }
    int mid = (l + r) / 2;
    P* left = create(l, mid);
    P* right = create(mid, r);
    return new P(left, right, 0);
}

void build() {
    trees.push_back(create(0, n));
}

P* _update(P* p, int cl, int cr, int idx, int val) {
    //if there is no overlap. 
    if(cl > idx || cr <= idx) {
        return p;
    }
    if(cl + 1 == cr) {
        return new P(val);
    }
    int mid = (cl + cr) / 2;
    P* left = _update(p->l, cl, mid, idx, val);
    P* right = _update(p->r, mid, cr, idx, val);
    return new P(left, right, left->val + right->val);
}

int update(int version, int node, int val) {
    P* root;
    if(version == -1) {
        root = trees.back();
    } else {
        root = trees[version];
    }
    trees.push_back(_update(root, 0, n, node, val));
    return trees.size() - 1;
}

int _query(P* p, int cl, int cr, int tl, int tr) {
    if(cr <= tl || cl >= tr) return 0;
    if(tl <= cl && cr <= tr) return p->val;
    int mid = (cl + cr) / 2;
    int lval = _query(p->l, cl, mid, tl, tr);
    int rval = _query(p->r, mid, cr, tl, tr);
    return lval + rval;
}

int query(int version, int l, int r) {
    return _query(trees[version], 0, n, l, r);
}

vector<string> split(string s, char delim) {
    vector<string> ret;
    for(int i = 0; i < s.size();) {
        if(s[i] == delim) {
            i ++;
            continue;
        }
        int r = i;
        while(r != s.size() && s[r] != delim) r ++;
        ret.push_back(s.substr(i, r - i));
        i = r;
    }
    return ret;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n;
    string trash;
    getline(cin, trash);
    build();

    vector<int> times(1 , 0);

    for(int i = 0; i < n; i++) {
        string s;
        getline(cin, s);
        vector<string> z(split(s, ' '));
        for(string op : z) {
            char c = op[0];
            int num = stoi(op.substr(1));
            if(c == '+') {
                update(-1, num, 1);
            } else {
                update(-1, num, 0);
            }
        }
        times.push_back(trees.size() - 1);
    }

    int x = 0;
    for(int i = 0; i < n; i++) {
        int d; cin >> d;
        int add = query(times[d], x, n);
        // cout << "i : " << i << " x : " << x << " times[d] : " << times[d] << " add : " << add << '\n';
        x = (x + add) % n;
    }

    cout << x << '\n';

    return 0;
}
