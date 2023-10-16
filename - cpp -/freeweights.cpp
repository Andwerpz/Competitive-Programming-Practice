#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Kattis - freeweights

bool isValid(int n, vector<vector<int>>& w, int val) {
    vector<vector<int>> a(2, vector<int>(0));
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < n; j++){
            if(w[i][j] > val) {
                a[i].push_back(w[i][j]);
            }
        }
    }
    if(a[0].size() % 2 == 1 || a[1].size() % 2 == 1){
        return false;
    }
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < a[i].size(); j += 2){
            if(a[i][j] != a[i][j + 1]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<vector<int>> w(2, vector<int>(n, 0));
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < n; j++){
            cin >> w[i][j];
        }
    }
    int low = 0;
    int high = 1e9;
    int ans = high;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(isValid(n, w, mid)) {
            ans = min(ans, mid);
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    cout << ans << "\n";
    
    return 0;
}
