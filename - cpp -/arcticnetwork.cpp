#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 09 A

//binary search across radio powers. 

bool isValid(vector<pair<ld, ld>>& a, int s, ld val) {
    int n = a.size();
    int cnt = 0;
    vector<bool> v(n, false);
    val *= val;
    for(int i = 0; i < n; i++){
        if(v[i]){
            continue;
        }
        v[i] = true;
        cnt ++;
        stack<int> st;
        st.push(i);
        while(st.size() != 0){
            int cur = st.top();
            st.pop();
            for(int j = 0; j < n; j++){
                if(v[j]){
                    continue;
                }
                ld dist = pow(a[cur].first - a[j].first, 2) + pow(a[cur].second - a[j].second, 2);
                if(dist < val) {
                    v[j] = true;
                    st.push(j);
                }
            }
        }
    }
    return cnt <= s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int s, n;
        cin >> s >> n;
        vector<pair<ld, ld>> a(n, {0, 0});
        for(int i = 0; i < n; i++){
            cin >> a[i].first >> a[i].second;
        }
        ld low = 0;
        ld high = 100000;
        ld mid = low + (high - low) / 2;
        ld ans = high;
        while(high - low > 1e-5) {
            if(isValid(a, s, mid)) {
                ans = min(ans, mid);
                high = mid;
            }
            else{
                low = mid;
            }
            mid = low + (high - low) / 2;
        }
        cout << fixed << setprecision(2) << ans << "\n";
    }
    
    return 0;
}
