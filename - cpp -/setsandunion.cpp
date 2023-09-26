#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1882B

//for each value, we can just try see what sets we exclude by not taking that value, and then for the remaining
//sets, find the union. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<vector<int>> h(51, vector<int>(0));
        for(int i = 0; i < n; i++){
            int k;
            cin >> k;
            for(int j = 0; j < k; j++){
                int next;
                cin >> next;
                h[next].push_back(i);
            }
        }
        int ans = 0;
        for(int i = 1; i <= 50; i++){
            set<int> s;
            if(h[i].size() == 0){
                continue;
            }
            for(int j = 0; j < h[i].size(); j++){
                s.insert(h[i][j]);
            }
            int curans = 0;
            for(int j = 1; j <= 50; j++){
                bool get = false;
                for(int k = 0; k < h[j].size(); k++){
                    if(s.find(h[j][k]) == s.end()) {
                        get = true;
                        break;
                    }
                }
                curans += get;
            }
            ans = max(ans, curans);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
