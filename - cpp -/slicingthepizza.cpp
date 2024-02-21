#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//UTPC Contest 02-09-24 Div. 2 - G

//since ⌊n/8⌋ of the points are guaranteed to be in a straight line, we can pick a random point and on average
//it'll take 8 tries to pick a point which is on the line. 

//if the point is on the line, there must be ⌊n/8⌋ - 1 other points that share the same slope. 

ll gcd(ll a, ll b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

void insert(map<pair<ll, ll>, ll>& m, pair<ll, ll> val) {
    if(m.find(val) == m.end()) {
        m.insert({val, 0});
    }
    m[val] ++;
}

bool is_valid(vector<pair<ll, ll>>& a, int sel, pair<ll, ll>& out_d) {
    map<pair<ll, ll>, ll> m;
    ll sx = a[sel].first;
    ll sy = a[sel].second;
    for(int i = 0; i < a.size(); i++){
        if(i == sel) {
            continue;
        }
        ll cx = a[i].first;
        ll cy = a[i].second;
        ll dx = cx - sx;
        ll dy = cy - sy;
        bool is_neg = (dx < 0) ^ (dy < 0);
        if(dx == 0){
            insert(m, {0, 1});
            continue;
        }
        if(dy == 0){
            insert(m, {1, 0});
            continue;
        }
        dx = abs(dx);
        dy = abs(dy);
        ll g = gcd(dx, dy);
        dx /= g;
        dy /= g;
        dy *= (is_neg? -1 : 1);
        insert(m, {dx, dy});
    }
    ll most = 0;
    for(auto i = m.begin(); i != m.end(); i++){
        ll cur_amt = i -> second + 1;
        if(cur_amt > most) {
            most = cur_amt;
            out_d = i -> first;
        }
    }
    return most >= a.size() / 8;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<pair<ll, ll>> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second;
    }
    srand(time(NULL));
    pair<ll, ll> out_d, pt;
    while(true) {
        int sel = (8127ll * rand()) % a.size();
        if(is_valid(a, sel, out_d)) {
            pt = a[sel];
            break;
        }
    }
    if(out_d.first == 0){
        //vertical line
        cout << "1 0 " << pt.first << "\n";
    }
    else if(out_d.second == 0){
        //horizontal line
        cout << "0 1 " << pt.second << "\n";
    }
    else {
        //some other line
        //y - y0 = m(x - x0)
        //y = mx - mx0 + y0
        //y + (-m)x = y0 - mx0
        lld slope = (lld) out_d.second / (lld) out_d.first;
        lld x0 = pt.first;
        lld y0 = pt.second;
        cout << fixed << setprecision(15) << (ld) (-slope) << " 1 " << (ld) (y0 - slope * x0) << "\n";
    }
    
    return 0;
}
