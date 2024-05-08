#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//ACPC 2024 Spring Contest - J

//use 2 queries to figure out the permutation, and the last to print the answer. 

//first query is to determine the remainder for each element, second one is to determine the multiple. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string s;
    cin >> s;
    string key = "abcdefghijklmnopqrstuvwxyz_,.?!():;";
    map<char, int> cmap;
    for(int i = 0; i < key.size(); i++){
        cmap[key[i]] = i;
    }
    int n = s.size();
    string out1 = "", out2 = "";
    for(int i = 0; i < n; i++){
        out1.push_back(key[i % key.size()]);
        out2.push_back(key[i / key.size()]);
    }
    string in1, in2;
    cout << out1 << endl;
    cin >> in1;
    cout << out2 << endl;
    cin >> in2;
    vector<int> p(n, -1);
    for(int i = 0; i < n; i++){
        int rem = cmap[in1[i]];
        int mult = cmap[in2[i]];
        p[i] = mult * key.size() + rem;
        // cout << p[i] << " ";
    }
    // cout << "\n";
    string out3(n, ' ');
    for(int i = 0; i < n; i++){
        out3[p[i]] = s[i];
    }
    cout << out3 << endl;
    
    return 0;
}
