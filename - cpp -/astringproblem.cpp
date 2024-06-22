#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1984D

//first, we can handle the edge case where the string consists of only 'a's. The answer is simply s.size() - 1. 

//so, now the string has to have at least one character that is not an 'a'. This means that t must contain a character
//that is not an 'a'. Since we must be able to fully represent the characters that are not 'a' with t, the amounts of
//non 'a' characters in t must divide the total amount, otherwise we would always have remainder leftover. 

//This actually makes it so that there aren't that many strings that we have to check for t, since it's equal
//to the amount of divisors of the count of non 'a' characters. Note that for a given t to be valid, it needs to divide 
//the totals for *all* non 'a' characters, which restricts it even more. 

//also note that some valid t has to be a substring of s, and it has to begin at the first non 'a' character. So, we can
//simply just find all t candidates, and test each of them in linear time. 

ll get_cnt(string& s, int _l, int _r) {
    vector<ll> gaps(0);
    gaps.push_back(_l);
    for(int i = _r; i <= s.size();) {
        int l = i;
        gaps.push_back(0);
        while(l != s.size() && s[l] == 'a') {
            gaps[gaps.size() - 1] ++;
            l ++;
        }
        if(l == s.size()) {
            break;
        }
        int r = l + (_r - _l);
        //check to see if they are equal
        if(s.substr(_l, _r - _l) != s.substr(l, r - l)) {
            return 0;
        }
        i = r;
    }
    //compute number of combinations
    if(gaps.size() == 2){
        return (gaps[0] + 1) * (gaps[1] + 1);
    }
    ll mid_min = 1e9;
    for(int i = 1; i < gaps.size() - 1; i++){
        mid_min = min(mid_min, gaps[i]);
    }
    ll ans = 0;
    for(ll i = 0; i <= min(mid_min, gaps[0]); i++){
        ans += min(mid_min - i, gaps[gaps.size() - 1]) + 1;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        string s;
        cin >> s;
        int l = -1;
        for(int i = 0; i < s.size(); i++){
            if(s[i] != 'a') {
                l = i;
                break;
            }
        }
        if(l == -1){
            //all 'a'
            cout << s.size() - 1 << "\n";
            continue;
        }
        //not all 'a'
        vector<int> tot(26, 0), cnt(26, 0);
        for(int i = 0; i < s.size(); i++){
            tot[s[i] - 'a'] ++;
        }
        ll ans = 0;
        for(int r = l + 1; r <= s.size(); r++){
            cnt[s[r - 1] - 'a'] ++;
            if(s[r - 1] == 'a') {
                continue;
            }
            bool is_div = true;
            for(int j = 1; j < 26; j++){
                if(tot[j] == 0){
                    continue;
                }
                if(cnt[j] == 0 || tot[j] % cnt[j] != 0) {
                    is_div = false;
                }
            }
            if(!is_div) {
                continue;
            }
            ans += get_cnt(s, l, r);
        }
        cout << ans << "\n";
    }
    
    return 0;
}