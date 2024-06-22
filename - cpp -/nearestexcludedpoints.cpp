#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1651D

//first, identify all points that are directly adjacent to some non-excluded point. Then just do bfs inwards. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    map<pair<int, int>, int> s;
    for(int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        a[i].first = x;
        a[i].second = y;
        s.insert({{x, y}, i});
    }
    vector<pair<int, int>> ans(n);
    //find all points that are directly adjacent to an excluded one
    vector<int> dx = {-1, 1, 0, 0};
    vector<int> dy = {0, 0, -1, 1};
    queue<int> q;
    vector<bool> v(n, false);
    for(int i = 0; i < n; i++) {
        int x = a[i].first;
        int y = a[i].second;
        for(int j = 0; j < 4; j++){
            int nx = x + dx[j];
            int ny = y + dy[j];
            if(!s.count({nx, ny})) {
                q.push(i);
                v[i] = true;
                ans[i] = {nx, ny};
                break;
            }
        }
    }
    //do bfs
    while(q.size() != 0){
        int ind = q.front();
        q.pop();
        int x = a[ind].first;
        int y = a[ind].second;
        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(!s.count({nx, ny})) {
                continue;
            }
            int nind = s[{nx, ny}];
            if(v[nind]) {
                continue;
            }
            v[nind] = true;
            q.push(nind);
            ans[nind] = ans[ind];
        }
    }
    for(int i = 0; i < n; i++){
        cout << ans[i].first << " " << ans[i].second << "\n";
    }
    
    return 0;
}