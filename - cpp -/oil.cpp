#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2016 G

//we can show that there must exist an optimal drill line that intersects two of the oil well endpoints exactly. 
//of course, if there is only one oil well, this doesn't hold. 

//for every oil well endpoint, we can just find the maximum amount of oil we can get given that we drill through that endpoint. 
//we can test each endpoint in n * log(n) time by doing a sweepline approach; order the rest of the endpoints by slope relative
//to the endpoint we're testing, and do an event based thing. 

ld pi = acos(-1);
ld epsilon = 1e-12;

ll solve(pair<ll, ll>&& origin, vector<vector<ll>>& a) {
    vector<pair<ld, ll>> s;
    for(ll i = 0; i < a.size(); i++){
        if(origin.second == a[i][2]) {
            continue;
        }
        ll oil = abs(a[i][0] - a[i][1]);
        {
            ld x = a[i][0] - origin.first;
            ld y = a[i][2] - origin.second;
            ld theta = atan2(y, x);
            if(theta < 0) {
                theta += pi;
            }
            if(y < 0) {
                s.push_back({theta - epsilon, oil});
            }
            else {
                s.push_back({theta, -oil});
            }
        }
        {
            ld x = a[i][1] - origin.first;
            ld y = a[i][2] - origin.second;
            ld theta = atan2(y, x);
            if(theta < 0) {
                theta += pi;
            }
            if(y < 0){
                s.push_back({theta, -oil});
            }
            else {
                s.push_back({theta - epsilon, oil});
            }
        }
    }
    sort(s.begin(), s.end());
    ll ans = 0;
    ll sum = 0;
    //cout << "CHECKING : " << origin.first << " " << origin.second << "\n";
    for(ll i = 0; i < s.size(); i++){
        //cout << s[i].first << " " << s[i].second << "\n";
        sum += s[i].second;
        ans = max(ans, sum);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n;
    cin >> n;
    vector<vector<ll>> a(n, vector<ll>(3));
    for(ll i = 0; i < n; i++){
        cin >> a[i][0] >> a[i][1] >> a[i][2];
        a[i][2] *= -1;
        if(a[i][0] > a[i][1]) {
            swap(a[i][0], a[i][1]);
        }
    }
    ll ans = 0;
    for(ll i = 0; i < n; i++){
        ll oil = abs(a[i][0] - a[i][1]);
        ans = max(ans, oil + solve({a[i][0], a[i][2]}, a));
        ans = max(ans, oil + solve({a[i][1], a[i][2]}, a));
    }
    cout << ans << "\n";
    
    return 0;
}
