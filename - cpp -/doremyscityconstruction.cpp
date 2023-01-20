#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1764C

//if all the nodes have the same value, then the answer is simply floor(n / 2). 

//we want to split the nodes into a high group, and low group, where all members of the high group have higher value
//than all the members in the low group. 

//Then we draw a connection from each member in the high group to each member in the low group, so the ans is len(high) * len(low). 
//now the problem is to maximize this product. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        vector<int> c(0);
        int cnt = 0;
        int prev = a[0];
        for(int i = 0; i < n; i++){
            if(a[i] != prev){
                c.push_back(cnt);
                cnt = 0;
            }
            prev = a[i];
            cnt ++;
        }
        c.push_back(cnt);
        ll ans = 0;
        ll pfx = 0;
        ll sfx = a.size();
        for(int i = 0; i < c.size() - 1; i++){
            pfx += c[i];
            sfx -= c[i];
            //cout << pfx << " " << sfx << "\n";
            ans = max(ans, pfx * sfx);
        }
        if(ans == 0){
            ans = n / 2;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
