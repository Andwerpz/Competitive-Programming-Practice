#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1986C

//it's optimal to place the characters that are the least in c at the beginning of s. 

//note that if there are duplicate indices, you can ignore all but one of them, since you just overwrite the last
//character you place there. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        string s, c;
        cin >> s;
        set<int> ind;
        for(int i = 0; i < m; i++){
            int next;
            cin >> next;
            ind.insert(next - 1);
        }
        cin >> c;
        sort(c.begin(), c.end());
        int ptr = 0;
        for(auto i = ind.begin(); i != ind.end(); i++){
            s[*i] = c[ptr];
            ptr ++;
        }
        cout << s << "\n";
    }
    
    return 0;
}