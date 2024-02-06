#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//NWERC 2020 - K

//just keep track of frequencies of characters from the first to second string. If a frequency changes,
//that key must be sticky. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string og, sticky;
    getline(cin, og);
    getline(cin, sticky);
    
    map<char,int> m;
    map<char,int> m2;
    for(char c : og) {
        m[c]++;
    }
    for(char c : sticky) {
        m2[c]++;
    }

    string diff = "";
    for(pair<char,int> p : m) {
        if(p.second != m2[p.first]) {
            diff.push_back(p.first);
        }
    }
    cout << diff << '\n';
    return 0;
}
