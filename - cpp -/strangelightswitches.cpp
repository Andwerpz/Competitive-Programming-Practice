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

//University of Alberta Programming Contest 2025 Open - I

//implementation. 

//it's impossible if your string consists only of '0' and '11' blocks (except for if s = "111", this is also impossible.)
//Otherwise, you can always solve it. First, make two '0's touching, and rotate the string so that they're at the front.
//then you can assimilate any string of '1's by first making them odd length, then switching them off. 

int off = 0;
vi a;
void rotate(int amt) {  //right to left rotation
    vi na(a.size());
    for(int i = 0; i < a.size(); i++){
        na[i] = a[(i + amt) % a.size()];
    }
    off += amt;
    a = na;
}

vi ans;
void toggle(int ind) {
    ans.push_back((ind + off) % a.size());
    a[ind] = a[(ind + a.size() - 1) % a.size()] ^ a[(ind + 1) % a.size()];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    string s;
    cin >> s;
    a = vi(n);
    for(int i = 0; i < n; i++) a[i] = s[i] - '0';
    //impossible
    bool impossible = false;
    if(s == "111") impossible = true;
    bool asdf = true;
    {
        int find = -1;
        for(int i = 1; i < n; i++){
            if(a[i] != a[0]) {find = i; break;}
        }
        rotate(find);
        for(int i = 0; i < n;){
            int rptr = i;
            while(rptr != n && a[rptr] == a[i]) rptr ++;
            int amt = rptr - i;
            if((a[i] == 0 && amt != 1) || (a[i] == 1 && amt != 2)) asdf = false;
            i = rptr;
        }
    }
    if(asdf) impossible = true;
    if(impossible) {
        cout << "-1\n";
        return 0;
    }
    //rotate until you can make 2 0s at front
    while(true){
        if(a[0] == 0 && a[1] == 0) break;
        if(a[0] == 0 && a[1] == 1 && a[2] == 0) {
            toggle(1);
            break;
        }
        if(n >= 4 && a[0] == 0 && a[1] == 1 && a[2] == 1 && a[3] == 1) {
            toggle(2);
            toggle(1);
            break;
        }
        rotate(1);
    }
    //solve rest of string
    for(int i = 2; i < n;){
        if(a[i] == 0) {i ++; continue;}
        int rptr = i;
        while(rptr != n && a[rptr] == 1) rptr ++;
        int amt = rptr - i;
        int l = i;
        if(amt % 2 == 0) {
            l --;
            toggle(l);
        }
        for(int j = l + 1; j < rptr; j += 2) toggle(j);
        for(int j = l; j < rptr; j += 2) toggle(j);
        i = rptr;
    }
    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++) cout << ans[i] << "\n";
    
    return 0;
}