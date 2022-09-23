#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        ll m;
        cin >> m;
        vector<ll> a(0);
        a.push_back(1);
        vector<pair<int, int>> ans(0);
        ans.push_back({m, 1});
        if(m != 2){
           ans.push_back({m, m - 1}); 
        }
        ll ptr = 2;
        while(a[a.size() - 1] < m){
            a.push_back(ptr + a[a.size() - 1]);
            ptr ++;
        }
        int k = 2;
        while(k <= a.size()) {
            // cout << "K: " << k << "\n";
            // for(int i : a){
            //     cout << i << " ";
            // }
            // cout << "\n";
            int n = a.size() + k - 1;
            if(a[a.size() - 1] == m){
                ans.push_back({n, k});
                if(k != a.size()){
                    ans.push_back({n, n - k});
                }
            }
            //generate next k
            k ++;
            vector<ll> next(0);
            next.push_back(1);
            while(next[next.size() - 1] < m){
                next.push_back(a[next.size()] + next[next.size() - 1]);
            }
            a = next;
        }
        sort(ans.begin(), ans.end(), [](pair<int, int> a, pair<int, int> b) {return a.first == b.first? a.second < b.second : a.first < b.first;});
        cout << ans.size() << "\n";
        for(pair<int, int> i : ans){
            cout << "(" << i.first << ", " << i.second << ") ";
        }
        cout << "\n";
    }
    
    return 0;
}
