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

//Codeforces - 873F

//first of all, we can reverse s and f and count occurrences that start with a non-forbidden character.

//next, let's compute the lcp array for the string. Now, if we view the lcp array a histogram, then we are just
//trying to find the largest rectangle in the histogram. This can be done in n * log(n) by sorting and DSU.

//keep in mind when computing the lcp array, we want to ignore suffixes that are forbidden. This can be done
//using a modification to kasai's algorithm. 

//Actually, on second thought, you don't even need to modify the algorithm. You can just do range minimum queries
//to compare D:

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

vi calc_lcp(vi suf_arr, vb& f, string& s) {
    int n = suf_arr.size();
    int k = 0;
    vector<int> lcp(n, 0);
    vector<int> rank(n, 0);
    for(int i = 0; i < n; i++) {
        rank[suf_arr[i]] = i;
    }
    for(int i = 0; i < n; i++, k? k-- : 0) {
        if(f[i]){
            continue;
        }
        int j = rank[i] + 1;
        while(j != n && f[suf_arr[j]]) {
            j ++;
        }
        if(j == n){
            k = 0;
            continue;
        }
        j = suf_arr[j];
        while(i + k < n && j + k < n && s[i + k] == s[j + k]) {
            k++;
        }
        lcp[rank[i]] = k;
    }
    vb v(n, false); vi tmp(0);
    for(int i = 0; i < n; i++){
        v[rank[i]] = !f[i];
    }
    for(int i = 0; i < n; i++){
        if(v[i]){
            tmp.push_back(lcp[i]);
        }
    }
    lcp = tmp;
    return lcp;
}

struct DSU {
    int N;
    vector<int> dsu, sz;

    DSU(int n) {
        this->N = n;
        this->dsu = vector<int>(n, 0);
        this->sz = vector<int>(n, 1);
        for(int i = 0; i < n; i++){ //initialize roots
            dsu[i] = i;
        }
    }

    int find(int a) {
        if(dsu[a] == a) {
            return a;
        }
        return dsu[a] = find(dsu[a]);
    }

    int get_sz(int a){
        return sz[find(a)];
    }

    //ret true if updated something
    bool unify(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if(ra == rb) {
            return false;
        }
        dsu[rb] = ra;
        sz[ra] += sz[rb];
        return true;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    string s;
    cin >> s;
    string line;
    cin >> line;
    vector<bool> f(n, false);
    for(int i = 0; i < n; i++){
        f[i] = line[i] - '0';
    }
    ll ans = 0;
    for(int i = n - 1; i >= 0; i--){
        if(!f[i]){
            ans = i + 1;
            break;
        }
    }
    reverse(s.begin(), s.end());
    reverse(f.begin(), f.end());
    f.push_back(false);
    vi suf = calc_suffix_array(s);
    vi lcp = calc_lcp(suf, f, s);
    n = lcp.size();
    DSU dsu(n);
    vector<pii> ord(0);
    for(int i = 0; i < n; i++){
        ord.push_back({lcp[i], i});
    }
    sort(ord.begin(), ord.end());
    reverse(ord.begin(), ord.end());
    vb v(n, false);
    for(int i = 0; i < n; i++){
        ll val = ord[i].first;
        int ind = ord[i].second;
        v[ind] = true;
        if(ind != 0 && v[ind - 1]){
            dsu.unify(ind, ind - 1);
        }
        if(ind != n - 1 && v[ind + 1]){
            dsu.unify(ind, ind + 1);
        }
        ans = max(ans, val * (dsu.get_sz(ind) + 1));
    }
    cout << ans << "\n";
    
    return 0;
}