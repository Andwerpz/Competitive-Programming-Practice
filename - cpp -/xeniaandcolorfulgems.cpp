#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Weekly Problem Set 2E

//lets say that you have an optimal solution r[i], g[j], b[k], where r[i] <= g[j] <= b[k]. 

//there cannot be another element in b that satisfies g[j] <= b[a] < b[k], likewise for r. 
//the elements picked from r and b must be the closest possible elements to g. 

//there are 6 possible orderings of r, g, b that we can test, so we can just test each one of them
//and return the minimal solution. 

ll getMin(vector<int>& a, vector<int>& b, vector<int>& c){
    int pa = 0;
    int pc = 0;
    ll min = 5e18;
    for(int i : b){
        while(pa + 1 != a.size() && a[pa + 1] <= i){
            pa ++;
        }
        while(pc + 1 != c.size() && c[pc] < i){
            pc ++;
        }
        ll da = a[pa] - i;
        ll db = c[pc] - i;
        ll dc = a[pa] - c[pc];
        min = std::min(min, da * da + db * db + dc * dc);
    }
    return min;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int nr, ng, nb;
        cin >> nr >> ng >> nb;
        vector<int> r(nr), g(ng), b(nb);
        for(int i = 0; i < nr; i++){
            cin >> r[i];
        }
        for(int i = 0; i < ng; i++){
            cin >> g[i];
        }
        for(int i = 0; i < nb; i++){
            cin >> b[i];
        }
        sort(r.begin(), r.end());
        sort(g.begin(), g.end());
        sort(b.begin(), b.end());
        ll ans = 5e18;
        ans = min(ans, getMin(r, g, b));
        ans = min(ans, getMin(r, b, g));
        ans = min(ans, getMin(g, r, b));
        ans = min(ans, getMin(g, b, r));
        ans = min(ans, getMin(b, r, g));
        ans = min(ans, getMin(b, g, r));
        cout << ans << "\n";
    }
    
    return 0;
}
