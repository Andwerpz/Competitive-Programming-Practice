#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1799 D1

//neat dp problem

//naive solution is to use a 3 state dp, n, k, k. 
//number of programs ran, previous program of cpu1, previous program of cpu2. 

//the problem is that complexity is O(n * k^2), which is too slow. 

//what we can notice is that after running program i, at least one of cpu1 and cpu2 must be equal
//to a[i]. 

//thus, we can get rid of a factor of k, since each program only needs k transitions, as opposed to k^2. 

//to solve hard version, you need to somehow do the k transitions in better than linear time, using some
//sort of datastructure like segment tree. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, k;
        cin >> n >> k;
        vector<int> a(n, 0);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            a[i] --;
        }
        vector<ll> cold(k, 0);
        vector<ll> hot(k, 0);
        for(int i = 0; i < k; i++){
            cin >> cold[i];
        }
        for(int i = 0; i < k; i++){
            cin >> hot[i];
        }
        vector<vector<ll>> dpa(2, vector<ll>(k + 1, 1e13));
        vector<vector<ll>> dpb(2, vector<ll>(k + 1, 0));
        dpa[0][k] = 0;
        dpa[1][k] = 0;
        for(int i = 0; i < n; i++){
            int prev = i == 0? k : a[i - 1];
            int cur = a[i];
            //first, go thru and set values
            for(int j = 0; j < k + 1; j++){
                dpb[0][j] = 1e13;
                dpb[1][j] = 1e13;
            }
            //now update
            for(int j = 0; j < k + 1; j++){
                //cpu1
                dpb[0][j] = min(dpb[0][j], dpa[0][j] + (prev == cur? hot[cur] : cold[cur])); 
                dpb[0][prev] = min(dpb[0][prev], dpa[1][j] + (j == cur? hot[cur] : cold[cur]));
                //cpu2
                dpb[1][j] = min(dpb[1][j], dpa[1][j] + (prev == cur? hot[cur] : cold[cur]));
                dpb[1][prev] = min(dpb[1][prev], dpa[0][j] + (j == cur? hot[cur] : cold[cur]));
            }
            swap(dpa, dpb);
        }
        ll ans = 1e18;
        for(int i = 0; i < k + 1; i++){
            ans = min(ans, dpa[0][i]);
            ans = min(ans, dpa[1][i]);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
