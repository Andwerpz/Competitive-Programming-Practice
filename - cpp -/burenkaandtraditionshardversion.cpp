#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1719D2

//as a baseline, it is always possible to reduce 'a' to only 0 using n seconds: for each a[i], just do
//a[i] ^ a[i]. 

//if a[l] ^ a[l + 1] ^ ... ^ a[r] = 0, then there is a way to reduce all a[i] where l >= i >= r in r - l 
//seconds, saving a second over the baseline. 

//so the solution is to maintain a set of pfx xors, and check for situations where a[l] ^ a[l + 1] ^ ... ^ a[r] = 0.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        int ans = n;
        set<int> s;
        vector<int> pfx(n);
        for(int i = 0; i < n; i++){
            cin >> pfx[i];
            if(i == 0){
                continue;
            }
            pfx[i] ^= pfx[i - 1];
        }
        s.insert(0);
        for(int i = 0; i < n; i++){
            if(s.find(pfx[i]) != s.end()){
                ans --;
                s.clear();
            }
            s.insert(pfx[i]);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
