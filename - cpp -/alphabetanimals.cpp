#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//NCPC 2019 - A

//implementation. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string first;
    cin >> first;
    int n;
    cin >> n;
    vector<string> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    map<char, int> s_map;
    for(int i = 0; i < 26; i++){
        s_map.insert({'a' + i, 0});
    }
    for(int i = 0; i < n; i++){
        if(s_map.find(a[i][0]) == s_map.end()) {
            s_map.insert({a[i][0], 0});
        }
        s_map[a[i][0]] ++;
    }
    bool found = false;
    bool found_good = false;
    string ans = "?";
    char need = *first.rbegin();
    s_map[need] --;
    for(int i = 0; i < n; i++){
        if(a[i][0] != need) {
            continue;
        }
        char last = *a[i].rbegin();
        if(!found) {
            found = true;
            ans = a[i];
        }
        if(!found_good && s_map[last] == 0) {
            found_good = true;
            ans = a[i] + "!";
        }
    }
    cout << ans << "\n";
    
    return 0;
}
