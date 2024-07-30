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
// typedef __int128 lll;
// typedef __float128 lld;

#include "segtree.cpp"

//this works by sorting all cyclic shifts of the string after appending '$' to it (lexicographically small character). 
vector<int> sort_cyclic_shifts(string const& s) {
    int n = s.size();
    const int alphabet = 256;
    vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
    for (int i = 0; i < n; i++)
        cnt[s[i]]++;
    for (int i = 1; i < alphabet; i++)
        cnt[i] += cnt[i-1];
    for (int i = 0; i < n; i++)
        p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i-1]])
            classes++;
        c[p[i]] = classes - 1;
    }
    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; ++h) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0)
                pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++)
            cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++)
            cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
            if (cur != prev)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}

vector<int> calc_suffix_array(string s) {
    s += "$"; 
    vector<int> sorted_shifts = sort_cyclic_shifts(s);
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}

//kasai's algorithm
vector<int> calc_lcp_array(string s){
    vector<int> suf = calc_suffix_array(s);
    int n = s.size();
    int k = 0;
    vector<int> lcp(n, 0);
    vector<int> rank(n, 0);
    for(int i = 0; i < n; i++) {
        rank[suf[i]] = i;
    }
    for(int i = 0; i < n; i++, k? k-- : 0) {
        if(rank[i] == n - 1){
            k = 0;
            continue;
        }
        int j = suf[rank[i] + 1];
        while(i + k < n && j + k < n && s[i + k] == s[j + k]) {
            k++;
        }
        lcp[rank[i]] = k;
    }
    return lcp;
}

struct LCP {
    int n;
    Segtree<int> segt;
    vector<int> ind_mp;
    LCP() {}
    LCP(string s) {
        n = s.size();
        vector<int> lcp = calc_lcp_array(s);
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return min(a, b);};
        segt = Segtree<int>(n, 0, 1e9, fmodify, fcombine); 
        segt.assign(lcp);
        vector<int> suf = calc_suffix_array(s);
        ind_mp = vector<int>(n);
        for(int i = 0; i < n; i++){
            ind_mp[suf[i]] = i;
        }
    }

    int get_lcp(int a, int b) {
        if(a == b){
            return n - a;
        }
        int l = min(ind_mp[a], ind_mp[b]);
        int r = max(ind_mp[a], ind_mp[b]);
        return segt.query(l, r);
    }
};