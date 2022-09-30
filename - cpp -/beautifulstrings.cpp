#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Weekly Problemset 3B

//just use a set. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    cin >> s;
    vector<int> a(26);
    for(int i = 0; i < s.size(); i++){
        char c = s[i];
        a[s[i] - 'a'] ++;
    }
    bool isValid = true;
    for(int i = 0; i < 26; i++){
        isValid &= a[i] % 2 == 0;
    }
    cout << (isValid? "Yes\n" : "No\n");
    
    return 0;
}
