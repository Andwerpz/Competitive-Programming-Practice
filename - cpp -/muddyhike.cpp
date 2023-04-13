#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 09 E

//binary search for minimum. 

vector<int> dr = {-1, 1, 0, 0};
vector<int> dc = {0, 0, -1, 1};

bool isValid(vector<vector<int>>& a, int val){
    vector<vector<bool>> v(a.size(), vector<bool>(a[0].size(), false));
    stack<pair<int, int>> s;
    for(int i = 0; i < a.size(); i++){
        if(a[i][0] <= val) {
            v[i][0] = true;
            s.push({i, 0});
        }
    }
    while(s.size() != 0){
        int r = s.top().first;
        int c = s.top().second;
        s.pop();
        if(c == a[0].size() - 1) {
            return true;
        }
        for(int i = 0; i < 4; i++){
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(nr < 0 || nc < 0 || nr >= a.size() || nc >= a[0].size()) {
                continue;
            }
            if(v[nr][nc]){
                continue;
            }
            if(a[nr][nc] > val){
                continue;
            }
            v[nr][nc] = true;
            s.push({nr, nc});
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> a[i][j];
        }
    }
    int low = 0;
    int high = 1e7;
    int mid = low + (high - low) / 2;
    int ans = high;
    while(low <= high){
        if(isValid(a, mid)) {
            ans = min(ans, mid);
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
        mid = low + (high - low) / 2;
    }
    cout << ans << "\n";
    
    return 0;
}
