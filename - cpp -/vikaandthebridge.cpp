#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1848B

//we can do an independent check for each color plank in the bridge. 

//for each plank, just store the index of the next plank with the same color. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            a[i] --;
        }
        vector<int> prev(k, -1);
        vector<int> next(n, n);
        for(int i = 0; i < n; i++){
            if(prev[a[i]] != -1){
                next[prev[a[i]]] = i;
            }
            prev[a[i]] = i;
        }
        set<int> s;
        int ans = 1e9;
        for(int i = 0; i < n; i++){
            if(s.find(a[i]) != s.end()) {
                continue;
            }
            s.insert(a[i]);
            vector<int> gap(0);
            gap.push_back(i);
            int ptr = i;
            while(ptr != n){
                gap.push_back(next[ptr] - ptr - 1);
                ptr = next[ptr];
            }
            sort(gap.begin(), gap.end());
            int curans = max(gap[gap.size() - 2], gap[gap.size() - 1] / 2);
            ans = min(ans, curans);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
