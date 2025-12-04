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

//TeamsCode Spring 2025 Advanced Division - H

//the trick here is to realize that this permutation composition where we do a'[i] = a[b[a[i]]], is 
//actually equivalent to matrix multiplication. So from now on, if we have two permutations a and b
//and I write ab, ab = c where c[i] = a[b[i]]. 

//lets look at how a, b, change when we perform some operations. 
//a b
//(a)b(a) b
//aba b(aba)b
//aba (babab)(aba)(babab)

//what we notice is that written in terms of the original a, b, the current ones are always just alternating a to b. 
//next, define p = ba, q = ab and let the current a, b be a' and b' respectively. Then, 
//a' = ap^{pcnt}, b' = bq^{qcnt}

//and after operations, this is how pcnt and qcnt change:
// 1: pcnt = 2 * pcnt + qcnt + 1
// 2: qcnt = 2 * qcnt + pcnt + 1

//notice that pcnt and qcnt get multiplied by 2 every time, so even binary exponentiation won't work. 
//however, remember that we're not multiplying matrices, we're actually composing permutations. And permutations 
//are just collections of cycles. Then, for each cycle length, we only have to keep track of the power modulo
//the cycle length. And since there can be at most sqrt(n) unique cycle lengths, we can keep track of this in 
//q * sqrt(n) time. 

//computes p[i] = a[b[i]]
vi compose(vi a, vi b) {
    int n = a.size();
    vi p(n);
    for(int i = 0; i < n; i++) p[i] = a[b[i]];
    return p;
}

map<int, vvi> cfind(vi &p) {
    map<int, vvi> c;
    int n = p.size();
    vb v(n, false);
    for(int i = 0; i < p.size(); i++){
        if(v[i]) continue;
        int ptr = i;
        vi cc;
        while(!v[ptr]) {
            v[ptr] = true;
            cc.push_back(ptr);
            ptr = p[ptr];
        }
        c[cc.size()].push_back(cc);
    }
    return c;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vi a(n), b(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];
    for(int i = 0; i < n; i++) a[i] --, b[i] --;
    int qcnt;
    cin >> qcnt;
    vi p = compose(b, a);
    vi q = compose(a, b);
    //find cycles of p, q
    map<int, vvi> cp = cfind(p), cq = cfind(q);
    //for each cycle length, keep track of composition count mod cycle length
    set<int> s;
    for(auto i = cp.begin(); i != cp.end(); i++) s.insert(i->first);
    for(auto i = cq.begin(); i != cq.end(); i++) s.insert(i->first);
    vector<pair<int, pll>> f;   //{m, {pcnt, qcnt}}
    for(auto i = s.begin(); i != s.end(); i++) f.push_back({*i, {0, 0}});
    for(int _ = 0; _ < qcnt; _++){
        int t;
        cin >> t;
        if(t == 1) {
            for(int i = 0; i < f.size(); i++){
                ll mod = f[i].first;
                ll pc = f[i].second.first;
                ll qc = f[i].second.second;
                f[i].second = {(pc * 2 + qc + 1) % mod, qc};
            }
        }
        else {  //t == 2
            for(int i = 0; i < f.size(); i++){
                ll mod = f[i].first;
                ll pc = f[i].second.first;
                ll qc = f[i].second.second;
                f[i].second = {pc, (qc * 2 + pc + 1) % mod};
            }
        }
    }
    //compute p^{pcnt}, q^{qcnt}
    map<int, ll> fp, fq;
    for(int i = 0; i < f.size(); i++){
        fp[f[i].first] = f[i].second.first;
        fq[f[i].first] = f[i].second.second;
    }
    vi pp(n), qq(n);
    for(int i = 0; i < n; i++) pp[i] = i, qq[i] = i;
    for(auto i = cp.begin(); i != cp.end(); i++){
        ll amt = fp[i->first];
        for(int j = 0; j < i->second.size(); j++){
            vi c = i->second[j];
            for(int k = 0; k < c.size(); k++){
                int ind = c[k];
                pp[ind] = c[(k + amt) % c.size()];
            }
        }
    }
    for(auto i = cq.begin(); i != cq.end(); i++){
        ll amt = fq[i->first];
        for(int j = 0; j < i->second.size(); j++) {
            vi c = i->second[j];
            for(int k = 0; k < c.size(); k++){
                int ind = c[k];
                qq[ind] = c[(k + amt) % c.size()];
            }
        }
    }
    //compute ap^{pcnt}, bq^{qcnt}
    vi ap = compose(a, pp);
    vi bq = compose(b, qq);
    for(int i = 0; i < n; i++) cout << ap[i] + 1 << " ";
    cout << "\n";
    for(int i = 0; i < n; i++) cout << bq[i] + 1 << " ";
    cout << "\n";
    
    return 0;
}