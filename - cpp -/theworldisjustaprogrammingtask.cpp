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

//Codeforces - 1239B

//mostly just guessforces. This is the sort of problem where writing a brute force checker pretty much gives
//you the answer. 

//the first observation you make is that if a bracket sequence has an equal number of '(' and ')', then 
//it's always a rotation away from a regular bracket sequence. If the bracket sequence doesn't have an
//equal amount of '(' and ')', then the beauty is always 0. 
//so we can always first rotate s such that it is a regular bracket sequence. 

//turns out that unless the answer is to just do nothing, it's always optimal to swap some pair of matched 
//brackets. Furthermore, swapping two matched brackets with depth > 2 will do nothing, so we just have to 
//check all pairs of matched brackets of depth 1 and 2. We can handle this using some casework. 

void rotate_to_rbs(string& s, int& off){
    int val = 0, minval = 0;
    // cout << "S : " << s << "\n";
    for(int i = 0; i < s.size(); i++){
        val += s[i] == '('? 1 : -1;
        // cout << val << " ";
        minval = min(minval, val);
    }
    // cout << "\n";
    val = 0;
    for(int i = s.size() - 1; i >= 0; i--){
        val += s[i] == '('? 1 : -1;
        if(val == -minval) {off = s.size() - i; break;}
    }
    // cout << "OFF : " << off << "\n";
    string ns(s.size(), ' ');
    for(int i = 0; i < s.size(); i++){
        ns[(i + off) % s.size()] = s[i];
    }
    s = ns;
}

string gen_rbs(int n) {
    string s(n, '(');
    for(int i = 0; i < n / 2; i++){
        while(true) {
            int ind = rand() % n;
            if(s[ind] == '(') {s[ind] = ')'; break;}
        }
    }
    int off = 0;
    rotate_to_rbs(s, off);
    return s;
}   

int beauty(string& s) {
    int val = 0, ans = 0;
    for(int i = 0; i < s.size(); i++){
        val += s[i] == '('? 1 : -1;
        ans += val == 0;
    }
    return ans;
}

pair<int, pii> solve_slow(string s){
    // cout << "SOLVE SLOW : " << s << "\n";
    pii ans = {0, 0};
    int ansb = 0;
    int n = s.size();
    int cnt = 0;
    vi a(n);
    for(int i = 0; i < s.size(); i++) cnt += s[i] == '('? 1 : -1, a[i] = cnt;
    vi id(n, -1);
    int idptr = 0;
    function<void(int&)> walk = [&s, &id, &idptr, &walk](int& ptr) -> void {
        int cid = idptr ++;
        id[ptr ++] = cid;
        while(s[ptr] == '(') walk(ptr);
        id[ptr ++] = cid;
    };
    int walkptr = 0;
    while(walkptr != n) {
        walk(walkptr);
    }
    // for(int i = 0; i < n; i++) cout << id[i] << " ";
    // cout << "\n";
    if(cnt != 0) return {ansb, ans};
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            string ns = s;
            swap(ns[i], ns[j]);
            int off;
            rotate_to_rbs(ns, off);
            int b = beauty(ns);
            if(b > ansb) {
                ansb = b;
                ans = {i, j};
                // cout << "NEW BEST : " << b << "\n" << ns << " " << a[i] << " " << a[j] << " " << id[i] << " " << id[j] << "\n";
            }
        }
    }
    assert(id[ans.first] == id[ans.second]);
    assert(a[ans.first] - a[ans.second] == 1);
    assert(a[ans.first] <= 2);
    if(a[ans.first] == 2) {
        assert(a[ans.first - 1] == 1);
        // cout << a[ans.first - 1] << " " << a[ans.second + 1] << endl;
        // assert(a[ans.first - 1] == 1 && a[ans.second + 1] == 0);
    }
    return {ansb, ans};
}

pair<int, pii> solve_fast(string s){
    // cout << "SOLVE FAST " << endl;
    pii ans = {0, 0};
    int ansb = 0;
    int n = s.size();
    int cnt = 0;
    for(int i = 0; i < s.size(); i++) cnt += s[i] == '('? 1 : -1;
    if(cnt != 0) return {ansb, ans};
    int totb = beauty(s);
    // ansb = totb;
    // ans = {1, 1};
    // cout << "TOTB : " << totb << endl;
    function<void(int&, int)> walk = [&](int& ptr, int depth) -> void {
        // cout << "WALK : " << ptr << " " << depth << endl;
        int cnt = 0;
        int l = ptr;
        ptr ++;
        while(s[ptr] == '(') cnt ++, walk(ptr, depth + 1);
        int r = ptr;
        ptr ++;
        int b = 0;
        if(depth == 0){
            b = 1 + cnt;
        }
        else if(depth == 1){
            b = totb + 1 + cnt;
        }
        if(b > ansb) {
            ansb = b;
            ans = {l, r};
        }
    };
    int ptr = 0;
    while(ptr != n) walk(ptr, 0);
    return {ansb, ans};
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n;
    cin >> n;
    string s;
    cin >> s;
    int cnt = 0;
    for(int i = 0; i < s.size(); i++) cnt += s[i] == '('? 1 : -1;
    if(cnt != 0) {
        cout << "0\n1 1\n";
        return 0;
    }
    int off;
    rotate_to_rbs(s, off);
    pair<int, pii> ans = solve_fast(s);
    ans.second.first = (n + ans.second.first - off) % n + 1;
    ans.second.second = (n + ans.second.second - off) % n + 1;
    cout << ans.first << "\n" << ans.second.first << " " << ans.second.second << "\n";
    
    // srand(time(0));
    // int cnt = 0;
    // while(true) {
    //     cnt ++;
    //     if(cnt % 100 == 0) cout << "CNT : " << cnt << endl;
    //     string s = gen_rbs(6);
    //     pair<int, pii> ans = solve_slow(s);
    //     pair<int, pii> ansf = solve_fast(s);
    //     assert(ans.first == ansf.first);
    //     cout << ans.first << " " << ansf.first << "\n";
    // }
    
    return 0;
}