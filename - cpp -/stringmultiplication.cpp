#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1131E

//seems pretty intimidating at first. Just need to realize that the only information you need about s
//when computing s * t is the maximum lengths of substrings for each character. 

//more formally, denote lng(s)[i] as the maximum length of a substring containing only character i in s. 
//Then, given some string t, we can compute lng(s * t) using some casework:

//if t consists of only 1 character c, then the procedure is 
//lng(s * t)[i] = max(1, lng(s)[i]), i != c
//lng(s * t)[i] = (lng(s)[i] + 1) * t.size() + lng(s)[i]

//otherwise, we can do this. Denote pfx(t) as the length of the longest pfx of t where all the characters are 
//the same, and sfx(t) is similarly defined. 
//lng(s * t)[i] = max(lng(t)[i], min(lng(s)[i], 1) + (i == t[0]? pfx(t) : 0) + (i == t[t.size() - 1]? sfx(t) : 0))

vector<ll> gen_lng(string& s) {
    vector<ll> lng(26, 0);
    int r = 0;
    for(int i = 0; i < s.size();){
        while(r != s.size() && s[i] == s[r]) {
            r ++;
        }
        lng[s[i] - 'a'] = max(lng[s[i] - 'a'], (ll) (r - i));
        i = r;
    }
    return lng;
}

void mult(vector<ll>& lng, string& t) {
    bool all_same = true;
    for(int i = 0; i < t.size() - 1; i++){
        if(t[i] != t[i + 1]) {
            all_same = false;
        }
    }
    if(all_same) {
        //edge case ig
        for(int i = 0; i < 26; i++){
            if(i == t[0] - 'a') {
                if(lng[i] != -1){
                    lng[i] = (lng[i] + 1) * t.size() + lng[i];
                }   
            }
            else {
                if(lng[i] != 0){
                    lng[i] = 1;
                }
            }
        }
    }
    else {
        //we only care about the beginning and end of t. 
        int pfx = 0;
        int sfx = 0;
        for(int i = 1; i < t.size(); i++){
            if(t[i] != t[i - 1]) {
                pfx = i;
                break;
            }
        }
        for(int i = t.size() - 2; i >= 0; i--){
            if(t[i] != t[i + 1]) {
                sfx = t.size() - 1 - i;
                break;
            }
        }
        vector<ll> tlng = gen_lng(t);
        for(int i = 0; i < 26; i++){
            if(lng[i] != 0){
                lng[i] = 1;
            }
            if(i == t[0] - 'a') {
                lng[i] += pfx;
            }
            if(i == t[t.size() - 1] - 'a') {
                lng[i] += sfx;
            }
            lng[i] = max(lng[i], tlng[i]);
        }
    }
    //clean up output array
    for(int i = 0; i < 26; i++){
        if(lng[i] > 1e9 || lng[i] < 0) {
            lng[i] = -1;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<string> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<ll> lng = gen_lng(a[0]);
    for(int i = 1; i < n; i++){
        mult(lng, a[i]);
        // for(int j = 0; j < 26; j++){
        //     cout << lng[j] << " ";
        // }
        // cout << "\n";
    }
    ll ans = 0;
    for(int i = 0; i < 26; i++){
        ans = max(ans, lng[i]);
    }
    cout << ans << "\n";
    
    return 0;
}