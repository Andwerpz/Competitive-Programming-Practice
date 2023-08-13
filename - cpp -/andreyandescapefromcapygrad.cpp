#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1859D

//if the starting point is outside of any range, then the answer is just the starting point. 

//for each range, we want to find the maximum distance we can travel to the right. 
//we can precompute this for each range. 

int query_rangeans(map<int, int>& rmap, int x) {
    if(rmap.size() == 0){
        return -1;
    }
    if(x < rmap.begin() -> first || x > rmap.rbegin() -> first) {
        return -1;
    }
    int ans = -1;
    auto lptr = rmap.lower_bound(x);
    if(lptr -> first != x){
        lptr --;
    }
    auto rptr = rmap.lower_bound(x);
    if(lptr -> second == rptr -> second) {
        ans = max(ans, lptr -> second);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<vector<int>> a(n, vector<int>(5, 0));
        for(int i = 0; i < n; i++){
            cin >> a[i][0] >> a[i][1] >> a[i][2] >> a[i][3];
        }
        //sort ranges according to max possible ans
        sort(a.begin(), a.end(), [](vector<int>& a, vector<int>& b) -> bool {
            return a[3] > b[3];
        });
        vector<bool> v(n, false);
        //maps ranges to answers
        map<int, int> rmap;
        for(int i = 0; i < n;){
            int cans = a[i][3];
            //see what answer we can get
            int l = a[i][0];
            int r = a[i][1];
            i ++;
            while(i < n){
                int ca = a[i][2];
                int cb = a[i][3];
                if(cb < l) {
                    break;
                }
                l = min(l, a[i][0]);
                r = max(r, a[i][1]);
                i ++;
            }
            //add our answer range to the map
            if(rmap.size() != 0){
                r = min(rmap.begin() -> first - 1, r);
            }
            rmap.insert({l, cans});
            rmap.insert({r, cans});
        }
        int q;
        cin >> q;
        while(q--){
            int x;
            cin >> x;
            int ans = max(x, query_rangeans(rmap, x));
            cout << ans << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
