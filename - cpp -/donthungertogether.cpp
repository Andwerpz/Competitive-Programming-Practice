#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC NAQ 2023 - C

//given some amount of food per person to eat, we can test in O(n * log(n)) whether or not it can pass
//the scenario. To test, we want to prioritize eating food that is closer to the expiration date. 

//then, we can just binary search over the amount of food to eat. 

bool is_valid(vector<pair<ld, int>>& a, ld val, ld k) {
    //cout << "TEST : " << val << "\n";
    priority_queue<pair<int, ld>> q;    //{-time food spoils, amt of food}
    for(int i = 0; i < a.size(); i++){
        //scavenge food
        q.push({-a[i].second, a[i].first});
        //eat food
        ld eat = k * val;
        //cout << "EAT : " << eat << "\n";
        while(true) {
            //cout << "REMAINING EAT : " << eat << "\n";
            if(q.size() == 0){
                return false;
            }
            int s_day = -q.top().first;
            ld food = q.top().second;
            q.pop();
            if(s_day < i){
                continue;
            }
            if(food > eat) {
                food -= eat;
                //cout << "PUSH FOOD BACK : " << food << "\n";
                q.push({-s_day, food});
                break;
            }
            //cout << "EAT FOOD : " << food << "\n";
            eat -= food;
        }
    }
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, k;
    cin >> n >> k;
    vector<pair<ld, int>> a(n, {0, 0});
    for(int i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second;
        a[i].second --;
    }
    // is_valid(a, 3.5, k);
    ld ans = -1;
    ld low = 1e-9;
    ld high = 1e10;
    while(high - low > 1e-10) {
        ld mid = low + (high - low) / 2.0;
        if(is_valid(a, mid, k)) {
            ans = max(ans, mid);
            low = mid;
        }
        else {
            high = mid;
        }
    }
    if(ans < 0){
        cout << "-1\n";
    }
    else {
        cout << fixed << setprecision(10) << ans << "\n";
    }
    
    return 0;
}
