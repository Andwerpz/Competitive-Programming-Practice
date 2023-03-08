#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        string s;
        cin >> s;
        int n = s.size();
        vector<int> c(26);
        for(int i = 0; i < n; i++){
            c[s[i] - '0'] ++;
        }
    }
    
    return 0;
}
