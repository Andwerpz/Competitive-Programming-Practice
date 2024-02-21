#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC NAQ 2023 - A

//just simulate the advancement algorithm. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k, c;
    cin >> n >> k >> c;
    vector<pair<int, int>> a(n, {0, 0});    //{team id, school id}
    for(int i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second;
    }
    vector<bool> adv(n, false);
    int adv_cnt = 0;
    map<int, int> m;
    for(int i = 0; i < n; i++){
        int school = a[i].second;
        if(m.find(school) == m.end()) {
            m.insert({school, 0});
        }
        if(m[school] < c && adv_cnt < k){
            adv_cnt ++;
            m[school] ++;
            adv[i] = true;
        }
    }
    for(int i = 0; i < n; i++){
        if(!adv[i] && adv_cnt < k){
            adv[i] = true;
            adv_cnt ++;
        }
    }
    for(int i = 0; i < n; i++){
        if(adv[i]) {
            cout << a[i].first << "\n";
        }
    }
    
    return 0;
}
