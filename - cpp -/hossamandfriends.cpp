#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces 1771B

//we can solve this using two pointers. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, m;
        cin >> n >> m;
        vector<vector<int>> c(n);
        for(int i = 0; i < m; i++){
            int a, b;
            cin >> a >> b;
            a --;
            b --;
            if(a > b){
                int tmp = a;
                a = b;
                b = tmp;
            }
            c[a].push_back(b);
        }
        map<int, int> mp;
        int r = 0;
        ll ans = 0;
        for(int i = 0; i < n; i++){
            while(r < n && (mp.size() == 0 || mp.begin() -> first > r)) {
                for(int j : c[r]) {
                    if(mp.find(j) == mp.end()){
                        mp.insert({j, 0});
                    }
                    mp.find(j) -> second ++;
                }
                r ++;
            }
            ans += r - i;
            for(int j : c[i]) {
                mp.find(j) -> second --;
                if(mp.find(j) -> second == 0) {
                    mp.erase(j);
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
