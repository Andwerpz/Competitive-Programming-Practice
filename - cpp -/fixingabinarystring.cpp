#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1979D

//In more simpler terms, what the operation does is you can pick any prefix, remove it from the string, reverse
//it, and append it to the end of the string. 

//so, what we can do is split the string into sections of equal characters. Looking at the last section, if it has
//size greater than k, then it's impossible to fix the string, as doing the operation can only increase the size
//of the last section. 

//if the size of the last section is equal to k, then there must exist another section in the string of length 2k in 
//order to be fixed. 

//otherwise, you have to find another section in the string that can supplement the last section up to length k. 
//If the string can be fixed, then there should only be 1 section that is able to do this. 

bool is_good(string& s, int k) {
    int n = s.size();
    char cur = s[0];
    for(int i = 0; i < n / k; i++){
        int l = i * k;
        for(int j = 0; j < k; j++){
            if(s[l + j] != cur) {
                return false;
            }
        }
        cur = cur == '1'? '0' : '1';
    }
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        if(is_good(s, k)) {
            cout << n << "\n";
            continue;
        }
        //split into groups of equal characters
        vector<int> g(0);
        for(int i = 0; i < n;){
            int r = i;
            while(r != s.size() && s[r] == s[i]) {
                r ++;
            }
            g.push_back(r - i);
            i = r;
        }    
        if(g[g.size() - 1] > k) {
            cout << "-1\n";
            continue;
        }
        bool foundp = false;
        int p = 0;
        if(g[g.size() - 1] == k){
            //there should be a group of size 2k somewhere
            for(int i = 0; i < g.size(); i++) {
                if(g[i] == 2 * k){
                    p += k;
                    foundp = true;
                    break;
                }
                p += g[i];
            }
        }
        else {
            //otherwise, last group needs to be supplemented. 
            char last_c = s[s.size() - 1];
            char cur = s[0];
            for(int i = 0; i < g.size() - 1; i++){
                if(cur == last_c) {
                    if(g[i] > k && g[i] - k + g[g.size() - 1] >= k){
                        p += k - g[g.size() - 1];
                        foundp = true;
                        break;
                    }
                    else if(g[i] < k) {
                        p += g[i];
                        foundp = true;
                        break;
                    }
                }
                cur = cur == '1'? '0' : '1';
                p += g[i];
            }
        }
        if(!foundp){
            cout << "-1\n";
            continue;
        }
        string pfx = s.substr(0, p);
        string sfx = s.substr(p);
        reverse(pfx.begin(), pfx.end());
        s = sfx + pfx;
        // cout << "NEW STRING : " << s << " " << p << "\n";
        cout << (is_good(s, k)? p : -1) << "\n";
    }
    
    return 0;
}