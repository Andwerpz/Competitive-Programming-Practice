#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC NAQ 2023 - I

//all the possible starting values, a, are just the prefixes of the string. 

//we can just try all of them, and see what possible missing numbers we get. 

//if true, then this is a valid string, might have one missing in the middle. 
bool is_valid(string& s, int a, int& out_missing, int& out_end) {
    int i = 0;
    out_missing = -1;
    while(i < s.size()) {
        string nr = to_string(a);
        if(i + nr.size() > s.size()) {
            return false;
        }
        if(s.substr(i, nr.size()) == nr) {
            a ++;
            i += nr.size();
            continue;
        }
        if(out_missing == -1){
            out_missing = a;
            a ++;
            continue;
        }
        return false;
    }
    out_end = a - 1;
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        string s;
        cin >> s;
        set<int> ans;
        for(int i = 0; i < 5; i++){
            if(i + 1 > s.size()) {
                break;
            }
            int start = stoi(s.substr(0, i + 1));
            int end = -1;
            int missing = -1;
            if(!is_valid(s, start, missing, end)) {
                continue;
            }
            if(missing != -1){
                ans.insert(missing);
            }
            else if(end <= 99999){
                if(start - 1 >= 1) {
                    ans.insert(start - 1);
                }
                if(end + 1 <= 99999) {
                    ans.insert(end + 1);
                }
            }
        }
        cout << ans.size() << "\n";
        for(auto i = ans.begin(); i != ans.end(); i++){
            if(*i > 99999) {
                break;
            }
            cout << *i << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
