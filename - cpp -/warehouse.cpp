#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//2018 South Central USA Regional - F

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        map<string, int> m;
        for(int i = 0; i < n; i++){
            string s;
            cin >> s;
            int amt;
            cin >> amt;
            m[s] += amt;
        }
        vector<pair<string, int>> a;
        cout << m.size() << "\n";
        for(auto i = m.begin(); i != m.end(); i++){
            a.push_back(*i);
        }
        sort(a.begin(), a.end(), [](pair<string, int>& a, pair<string, int>& b) -> bool {
            if(a.second != b.second) {
                return a.second > b.second;
            }
            return a.first < b.first;
        });
        for(int i = 0; i < a.size(); i++){
            cout << a[i].first << " " << a[i].second << "\n";
        }
    }
    
    return 0;
}
