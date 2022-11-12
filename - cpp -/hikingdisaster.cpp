#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<vector<int>> s(0);
    for(int i = 0; i < n; i++){
        if(a[i] != k){
            vector<int> next(0);
            while(i != n && a[i] != k){
                next.push_back(a[i]);
                i ++;
            }
            i --;
            s.push_back(next);
        }
    }
    ll ans = 0;
    for(vector<int> v : s){
        map<int, int> m;
        int r = 0;
        for(int i = 0; i < v.size(); i++){
            //cout << v[i] << " ";
            while(r <= i || (r != v.size() && m.size() != k)) {
                int next = v[r];
                if(next > k){
                    r ++;
                    continue;
                }
                if(m.find(next) == m.end()){
                    m.insert({next, 0});
                }
                m.find(next) -> second ++;
                r ++;
            }
            //cout << r << " ";
            if(m.size() == k){
                ans += (ll) (v.size() - r + 1);
            }
            int remove = v[i];
            if(m.find(remove) != m.end()){
                m.find(remove) -> second --;
                if(m.find(remove) -> second == 0){
                    m.erase(remove);
                }
            }
        }
    }
    cout << ans << "\n";
    
    return 0;
}
