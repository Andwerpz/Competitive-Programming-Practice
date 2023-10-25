#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Kattis - suffixarrayreconstruction

//we can just brute force try to reconstruct the string, while checking for inconsistencies along the way.

//since we are told the position of each suffix, this is pretty easy. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, s;
        cin >> n >> s;
        vector<char> c(n, '*');
        bool is_valid = true;
        for(int i = 0; i < s; i++){
            int pos;
            cin >> pos;
            pos --;
            string suf;
            cin >> suf;
            int tgt_size = n - pos;
            int asterisk_nr = tgt_size - suf.size() + 1;
            int ptr = pos;
            for(int j = 0; j < suf.size(); j++){
                if(suf[j] == '*') {
                    ptr += asterisk_nr;
                    continue;
                }
                if(c[ptr] != '*' && c[ptr] != suf[j]) {
                    is_valid = false;
                }
                c[ptr] = suf[j];
                ptr ++;
            }
        }
        for(int i = 0; i < c.size(); i++){
            if(c[i] == '*') {
                is_valid = false;
            }
        }
        if(!is_valid) {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        for(int i = 0; i < c.size(); i++){
            cout << c[i];
        }
        cout << "\n";
    }
    
    return 0;
}
