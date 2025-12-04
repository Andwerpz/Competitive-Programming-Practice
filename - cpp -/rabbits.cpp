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

//Codeforces - 2147C

//we can parse the string into separated components of flowers and rabbits. Observe that if you have a flower
//component of size 2 or more, then you can treat the parts to the left and right as independent problems.

//So we can just consider when our array only has flower components of size 1. Observe that a rabbit component
//of size 2 or more is self-stabilizing, as you can have a pair of rabbits facing eachother. Rabbit components
//of size 1 need external stabilization. 

//next, a rabbit component of size 2 can optionally provide external stabilization to both components to left 
//and right, while a component of size 1 can only provide support to one of left or right. 

//If there exists a rabbit component of size 2, then it's always possible as that component can adjust parity
//as needed. If there does not exist a component of size 2, then it's only possible iff the number of components 
//is even, as then we can pair up the size 1 components to support each other. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;
        if(s[s.size() - 1] == '0') {
            s.push_back('1');
            s.push_back('0'), s.push_back('0');
        }
        reverse(s.begin(), s.end());
        if(s[s.size() - 1] == '0') {
            s.push_back('1');
            s.push_back('0'), s.push_back('0');
        }
        bool ans = true;
        vector<pii> a(0);   //{type, amt}
        for(int i = 0; i < s.size();) {
            int r = i;
            while(r != s.size() && s[r] == s[i]) {
                r ++;
            }
            a.push_back({s[i] - '0', r - i});
            i = r;
        }
        // for(int i = 0; i < a.size(); i++) cout << a[i].first << " " << a[i].second << "\n";
        // assert(a.size() > 2);
        // assert(a.size() % 2 == 1);
        for(int i = 0; i < a.size();) {
            if(a[i].first == 1) {
                i ++;
                continue;
            }
            int r = i + 1;
            while(r + 2 <= a.size() && a[r].second == 1) r += 2;
            bool has_nonone = false;
            int amt = 0;
            for(int j = i; j < r; j += 2) {
                if(a[j].second != 1) has_nonone = true;
                amt ++;
            }
            // cout << "ASDF : " << has_nonone << " " << amt << " " << i << " " << r << "\n";
            if(!has_nonone && (amt % 2)) ans = false;
            i = r + 1;
        }
        cout << (ans? "YES" : "NO") << "\n";
    }
    
    return 0;
}