#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1832A

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        string s;
        cin >> s;
        vector<int> a(26, 0);
        for(int i = 0; i < s.size() / 2; i++){
            a[s[i] - 'a'] ++;
        }
        int two = 0;
        for(int i = 0; i < 26; i++){
            two += a[i] != 0;
        }
        cout << (two >= 2 ? "YES\n" : "NO\n");
    }
    
    return 0;
}
