#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//A&M Fall 2022 D

//meet in the middle

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, l, r;
    cin >> n >> l >> r;
    vector<pair<ll, ld>> a((n + 1) / 2);
    vector<pair<ll, ld>> b((n - 1) / 2);
    for(int i = 0; i < n; i++){
        if(i < (n + 1) / 2){
            cin >> a[i].first >> a[i].second;
            a[i].second /= 100.0;
        }
        else {
            cin >> b[i - (n + 1) / 2].first >> b[i - (n + 1) / 2].second;
            b[i - (n + 1) / 2].second /= 100.0;
        }
    }
    vector<pair<ll, ld>> aSet(0);
    vector<pair<ll, ld>> bSet(0);
    aSet.push_back({0, 1});
    bSet.push_back({0, 1});
    for(int i = 0; i < a.size(); i++){
        vector<pair<ll, ld>> next(0);
        ll amt = a[i].first;
        ld prob = a[i].second;
        for(pair<ll, ld> j : aSet){
            next.push_back({j.first + amt, j.second * prob});
            next.push_back({j.first, j.second * (1.0 - prob)});
        }
        aSet = next;
    }
    // for(pair<ll, ld> i : aSet){
    //     cout << i.first << " " << i.second << "\n";
    // }
    // cout << endl;
    for(int i = 0; i < b.size(); i++){
        vector<pair<ll, ld>> next(0);
        ll amt = b[i].first;
        ld prob = b[i].second;
        for(pair<ll, ld> j : bSet){
            next.push_back({j.first + amt, j.second * prob});
            next.push_back({j.first, j.second * (1.0 - prob)});
        }
        bSet = next;
    }
    bSet.push_back({-1, 0});
    bSet.push_back({1e10, 0});
    sort(bSet.begin(), bSet.end(), [](pair<ll, ld>& a, pair<ll, ld>& b) -> bool {return a.first < b.first;});
    vector<ld> bSetPfx(0);
    bSetPfx.push_back(bSet[0].second);
    for(int i = 1; i < bSet.size(); i++){
        bSetPfx.push_back(bSetPfx[i - 1] + bSet[i].second);
    }
    ld ans = 0;
    for(int i = 0; i < aSet.size(); i++){
        ld amt = aSet[i].first;
        ld prob = aSet[i].second;
        //cout << amt << " " << prob << "\n";
        if(amt + bSet[1].first > r || amt + bSet[bSet.size() - 2].first < l){
            continue;
        }
        int upper = 0;
        int lower = bSet.size() - 1;
        int low = 1;
        int high = bSet.size() - 2;
        int mid = low + (high - low) / 2;
        while(low <= high){
            if(bSet[mid].first + amt <= r){
                upper = max(mid, upper);
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
            mid = low + (high - low) / 2;
        }
        low = 1;
        high = bSet.size() - 2;
        mid = low + (high - low) / 2;
        while(low <= high){
            if(bSet[mid].first + amt >= l){
                lower = min(lower, mid);
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
            mid = low + (high - low) / 2;
        }
        //cout << upper << " " << lower << "\n";
        ans += prob * (bSetPfx[upper] - bSetPfx[lower - 1]);
        //cout << ans << "\n";
    }
    cout.precision(17);
    cout << ans * 100.0 << fixed << "\n";
    
    return 0;
}
