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

//Codeforces - 1304B

//just check for each string if there is a matching reverse string. Then, in the final palindrome, place 
//the string and it's reverse at opposite ends of the palindrome. 

//If there exists an extra palindrome, we can also place that at the center, so check for that in all
//the leftovers. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<string> t;
    set<string> s;
    for(int i = 0; i < n; i++){
        string tmp = a[i];
        reverse(tmp.begin(), tmp.end());
        if(s.count(tmp)) {
            s.erase(tmp);
            t.push_back(a[i]);
            continue;
        }
        s.insert(a[i]);
    }
    string pal = "";
    for(auto i = s.begin(); i != s.end(); i++){
        string tmp = *i;
        string rev = tmp;
        reverse(rev.begin(), rev.end());
        if(rev == tmp){
            pal = tmp;
            break;
        }
    }
    string ans = "";
    for(int i = 0; i < t.size(); i++){
        ans += t[i];
    }
    ans += pal;
    for(int i = t.size() - 1; i >= 0; i--){
        reverse(t[i].begin(), t[i].end());
        ans += t[i];
    }
    cout << ans.size() << "\n" << ans << "\n";
    
    return 0;
}