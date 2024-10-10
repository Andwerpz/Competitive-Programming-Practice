#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Kattis - oddmanout

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    int caseno = 0;
    while(t--){
        caseno ++;
        int n;
        cin >> n;
        set<int> s;
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            if(!s.count(next)) {
                s.insert(next);
            }
            else {
                s.erase(s.find(next));
            }
        }
        cout << "Case #" << caseno << ": " << *s.begin() << "\n";
    }
    
    return 0;
}
