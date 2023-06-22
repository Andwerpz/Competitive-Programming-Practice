#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1841D

//generate all possible unions of pairs of segments, and put them into an array. 

//then, the problem is to choose as many non-intersecting unions as possible. 
//this problem is just like the scheduling problem with a greedy solution. 

//note that it is impossible to choose a segment twice, since a segment has to be continuous. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<pair<int, int>> a(n, {0, 0});
        for(int i = 0; i < n; i++){
            cin >> a[i].first >> a[i].second;
        }
        vector<pair<int, int>> u(0);
        for(int i = 0; i < n; i++){
            int l1 = a[i].first;
            int r1 = a[i].second;
            for(int j = i + 1; j < n; j++){
                int l2 = a[j].first;
                int r2 = a[j].second;
                if(r1 < l2 || l1 > r2) {
                    continue;
                }
                u.push_back({min(l1, l2), max(r1, r2)});
            }
        }
        sort(u.begin(), u.end(), [](pair<int, int>& a, pair<int, int>& b) {return a.second < b.second;});
        int r = -1;
        int ans = n;
        for(int i = 0; i < u.size(); i++){
            if(u[i].first > r) {
                r = u[i].second;
                ans -= 2;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
