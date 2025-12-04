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

//ECNA 2023 - I

//another reading comprehension problem lmao

//except, this one has a tricky edge case, make sure that you're not accepting a 'X' anywhere else than the last character. 

bool isv(string s) {
    //check for invalid hyphen placement
    int hcnt = 0;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '-') hcnt ++;
        if(i != s.size() - 1 && s[i] == '-' && s[i + 1] == '-') return false;
    }
    if(s[0] == '-' || s[s.size() - 1] == '-') return false;
    if(hcnt > 3) return false;
    if(hcnt == 3 && s[s.size() - 2] != '-') return false;

    //extract digits
    vi a;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] != '-') {
            if(s[i] == 'X') {
                if(i != s.size() - 1) return false;
                a.push_back(10);
            }
            else a.push_back(s[i] - '0');
        }
    }
    if(a.size() != 10) return false;

    //checksum
    int sum = 0;
    for(int i = 0; i < 10; i++) {
        sum += (10 - i) * a[i];
        sum %= 11;
    }
    if(sum != 0) return false;

    return true;
}   

string cnv(string s) {
    //extract digits
    vi a = {9, 7, 8};
    for(int i = 0; i < s.size(); i++) {
        if(s[i] != '-') {
            if(s[i] == 'X') a.push_back(10);
            else a.push_back(s[i] - '0');
        }
    }
    assert(a.size() == 13);
    
    //new checksum
    int sum = 0;
    for(int i = 0; i < 12; i++) {
        sum += ((i % 2 == 0)? 1 : 3) * a[i];
        sum %= 10;
    }
    a[12] = (10 - sum) % 10;
    s[s.size() - 1] = '0' + a[12];

    return "978-" + s;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        string s;
        cin >> s;
        if(!isv(s)) {
            cout << "invalid\n";
        }
        else cout << cnv(s) << "\n";
    }
    
    return 0;
}