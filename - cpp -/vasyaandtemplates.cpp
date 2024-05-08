#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1085E

//this isn't worth my time to optimize the constant factor. 
//the idea is correct tho. 

//returns minimized template starting at an index
string minim(string& s, set<char> vb, map<char, char> m, int start, int k) {
    for(int i = start; i < s.size(); i++){
        if(m.find(s[i]) != m.end()) {
            continue;
        }
        m[s[i]] = *vb.begin();
        vb.erase(vb.begin());
    }
    for(int i = 0; i < k; i++){
        if(m.find('a' + i) == m.end()) {
            m['a' + i] = *vb.begin();
            vb.erase(vb.begin());
        }
    }
    string t = "";
    for(int i = 0; i < m.size(); i++){
        t.push_back(m['a' + i]);
    }
    return t;
}

bool is_template_valid(string s, string& a, string& b, string& t) {
    for(int i = 0; i < s.size(); i++){
        s[i] = t[s[i] - 'a'];
    }
    return a <= s && s <= b;
}

//we'll assign s[ind] -> nc in the template, and then minimize the result
string nc_gen_min(int ind, set<char> vb, map<char, char> m, string& s, char nc, int k) {
    m[s[ind]] = nc;
    vb.erase(nc);
    return minim(s, vb, m, ind + 1, k);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int k;
        cin >> k;
        string s, a, b;
        cin >> s >> a >> b;
        int n = s.size();
        if(n == 1){
            string tmpl(k, 'a');
            for(int i = 0; i < k; i++){
                tmpl[i] = 'a' + i;
            }
            tmpl[s[0] - 'a'] = a[0];
            tmpl[a[0] - 'a'] = s[0];
            cout << "YES\n";
            cout << tmpl << "\n";
            continue;
        }
        set<char> vb;
        for(int i = 0; i < k; i++){
            vb.insert('a' + i);
        }
        map<char, char> m;
        bool is_valid = false;
        string ans = "";
        for(int i = 0; i < n; i++){
            //if s[i] has already been taken
            if(m.count(s[i])) {
                char cur = m[s[i]];
                if(cur < a[i]) {
                    break;
                }
                else if(cur == a[i]) {
                    continue;
                }
                //just minimize
                string tmpl = nc_gen_min(i, vb, m, s, cur, k);
                if(is_template_valid(s, a, b, tmpl)) {
                    is_valid = true;
                    ans = tmpl;
                }
                break;
            }
            //choose minimum character in vb that hasn't been assigned yet
            char nc = 0;
            for(auto j = vb.begin(); j != vb.end(); j++){
                if(*j > a[i]) {
                    nc = *j;
                    break;
                }
            }
            if(nc != 0){
                string tmpl = nc_gen_min(i, vb, m, s, nc, k);
                if(is_template_valid(s, a, b, tmpl)) {
                    is_valid = true;
                    ans = tmpl;
                }
            }
            //just set s[i] -> a[i]
            if(vb.count(a[i])) {
                m[s[i]] = a[i];
                vb.erase(vb.find(a[i]));
            }
            else {
                break;
            }
        }
        if(ans.size() == 0){
            string tmpl = minim(s, vb, m, n, k);
            // cout << "GEN TMPL : " << tmpl << "\n";
            if(is_template_valid(s, a, b, tmpl)) {
                is_valid = true;
                ans = tmpl;
            }
        }
        if(is_valid) {
            cout << "YES\n";
            cout << ans << "\n";
        }
        else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
