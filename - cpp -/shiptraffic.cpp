#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2015 I

//note that if a ship is travelling to the east, it's as if it's mirrored around the ferry line and travelling to the west. 
//we can make all ships travel in the same direction. 

//then, we can put all ships into the first lane by offsetting them by the time required by the ferry to get into their lane. 

//then, we just need to find the maximum segment of time where there is no ship. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ld n, w, u, v, t1, t2; cin >> n >> w >> u >> v >> t1 >> t2;

    // vector<pair<ld,ld>> a(0);
    vector<pair<ld, int>> a(0);
    for(int i = 0; i < n; i++) {
        char d; cin >> d;
        int boats; cin >> boats;
        for(int j = 0; j < boats; j++) {
            ld l, p; cin >> l >> p;
            if(d == 'E') {
                p *= -1;
            }
            ld start = p / u - i * w / v;
            ld stop = start + l / u;
            // a.push_back({start, stop});
            a.push_back({start, 1});
            a.push_back({stop, -1});
        }
    }

    a.push_back({-1e6, 1});
    a.push_back({t1, -1});
    a.push_back({t2 + 1e7, 1});
    a.push_back({1e9, -1});

    //cout << "FERRY SPEED : " << v << "\n";
    //cout << "LANE WIDTH : " << w << "\n";
    //cout << "BOAT SPEED : " << u << "\n";
    
    sort(a.begin(), a.end());
    int curr = 0;
    ld start = 0;
    ld ans = 0;
    for(int i = 0; i < a.size(); i++) {
        
        curr += a[i].second;
        if(curr == 0){
            //update answer
            start = max(a[i].first, t1);
            ld end = t2;
            if(i != a.size() - 1){
                end = min(end, a[i + 1].first - w / v);
            }
            //cout << "UPD ANSWER : " << start << " " << end << "\n";
            ans = max(end - start, ans);
        }
    }

    cout << fixed << setprecision(10) << ans << "\n";

    return 0;
}
