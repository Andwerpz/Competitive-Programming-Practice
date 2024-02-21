#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//2018 South Central USA Regional - C

//we can just store all character counts of all substrings of B in a set, and then brute force search all 
//substrings of A. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        string a, b;
        cin >> a >> b;
        int n = a.size();
        map<vector<int>, pair<int, int>> b_map; //{left, length}
        for(int i = 0; i < n; i++){
            vector<int> key(26, 0);
            for(int j = i; j < n; j++){
                key[b[j] - 'a'] ++;
                b_map.insert({key, {j, j - i + 1}});
            }
        }
        int longest = 0;
        int left = 0;
        for(int i = 0; i < n; i++){
            vector<int> key(26, 0);
            for(int j = i; j < n; j++){
                key[a[j] - 'a'] ++;
                if(b_map.count(key)) {
                    // cout << "FOUND KEY" << "\n";
                    int len = b_map[key].second;
                    int l = b_map[key].first;
                    if(len > longest) {
                        longest = len;
                        left = i;
                    }
                }
            }
        }
        if(longest == 0){
            cout << "NONE\n";
        }
        else {
            cout << a.substr(left, longest) << "\n";
        }
    }
    
    return 0;
}
