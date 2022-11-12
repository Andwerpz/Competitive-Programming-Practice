#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(0);    //location, change, dank:1 ; murky:-1
    for(int i = 0; i < m; i++) {
        int x, r;
        string t;
        cin >> x >> r >> t;
        int type = t == "dank"? 1 : -1;
        a.push_back({x - r, 1, type});
        a.push_back({x + r + 1, -1, type});
    }
    int dank = 0;
    int murky = 0;
    sort(a.begin(), a.end(), [](vector<int>& a, vector<int>& b) -> bool {return a[0] < b[0];});
    // for(vector<int> i : a){
    //     for(int j : i){
    //         cout << j << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    int ans = 0;
    int prev = 0;
    for(int i = 0; i < a.size(); i += 0){
        //cout << i << " inter" << endl;
        int cur = a[i][0];
        if(i != 0){
            int tCur = cur;
            int tPrev = prev;
            tCur = max(tCur, 1);
            tPrev = max(tPrev, 1);
            tCur = min(tCur, n + 1);
            tPrev = min(tPrev, n + 1);
            int diff = tCur - tPrev;
            if(dank + murky >= 4 && dank == murky){
                ans += diff;
            }
        }
        while(i < a.size() && a[i][0] == cur){
            //cout << i << "LOOP" << endl;
            int change = a[i][1];
            int type = a[i][2];
            if(type == 1){
                dank += change;
            }
            else {
                murky += change;
            }
            i += 1;
        }
        //cout << cur << " " << dank << " " << murky << endl;
        prev = cur;
    }
    cout << ans << "\n";
    
    return 0;
}
