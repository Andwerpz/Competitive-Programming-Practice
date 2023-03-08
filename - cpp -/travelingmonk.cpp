#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 07 D

//binary search across all times
//you can validate in linear time by just simulating where the monk will be on the ascent and descent. 

bool isValid(vector<pair<ld, ld>>& asc, vector<pair<ld, ld>>& dsc, ld sum, ld val) {
    ld a = 0.00000001;
    ld d = sum;
    ld ptr = val;
    for(int i = 0; i < asc.size(); i++){
        if(ptr > asc[i].second) {
            a += asc[i].first;
        }
        else {
            a += asc[i].first * (ptr / asc[i].second);
            break;
        }
        ptr -= asc[i].second;
    }
    ptr = val;
    for(int i = 0; i < dsc.size(); i++){
        if(ptr > dsc[i].second){
            d -= dsc[i].first;
        }
        else {
            d -= dsc[i].first * (ptr / dsc[i].second);
            break;
        }
        ptr -= dsc[i].second;
    }
    return a > d;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int a, d;
    cin >> a >> d;
    ld sum = 0;
    vector<pair<ld, ld>> asc(a, {0, 0});
    vector<pair<ld, ld>> dsc(d, {0, 0});
    for(int i = 0; i < a; i++){
        cin >> asc[i].first >> asc[i].second;
        sum += asc[i].first;
    }
    for(int i = 0; i < d; i++){
        cin >> dsc[i].first >> dsc[i].second;
    }
    ld ans = 1e9;
    ld low = 0;
    ld high = 1e9;
    ld mid = low + (high - low) / 2;
    while(high - low > 1e-7) {
        if(isValid(asc, dsc, sum, mid)) {
            ans = min(ans, mid);
            high = mid;
        }
        else {
            low = mid;
        }
        mid = low + (high - low) / 2;
    }
    cout << fixed << setprecision(10) << ans << "\n";
    
    return 0;
}
