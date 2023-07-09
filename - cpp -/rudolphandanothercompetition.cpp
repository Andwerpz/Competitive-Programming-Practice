#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1846C

//the optimal order to solve problems is to solve them in ascending order based on time taken to solve. 
//this will allow you to solve the most problems, and keep your penalty minimal. 

//you can't naively put everything into arrays, as it's too slow. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m, h;
        cin >> n >> m >> h;
        int ans = 1;
        pair<int, ll> f;
        vector<ll> a(m);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cin >> a[j];
            }
            sort(a.begin(), a.end());
            ll ptr = 0;
            int nsolve = 0;
            ll pen = 0;
            for(int j = 0; j < m; j++){
                ptr += a[j];
                if(ptr > h) {
                    break;
                }
                nsolve ++;
                pen += ptr;
            }
            if(i == 0){
                f = {nsolve, pen};
                continue;
            }
            if(nsolve > f.first || (nsolve == f.first && pen < f.second)) {
                ans ++;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
