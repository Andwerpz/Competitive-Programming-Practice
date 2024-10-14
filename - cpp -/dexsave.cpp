#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//KTH Challenge 2021 - D

//implementation. Can just use map to keep track of probabilities. 
//however, have to be careful of edge case where you roll a 1 or 20 on first roll. 

map<int, ld> shift_prob(map<int, ld> p, int amt) {
    map<int, ld> newp;
    for(auto i = p.begin(); i != p.end(); i++){
        newp[i->first + amt] = i->second;
    }
    return newp;
}

map<int, ld> do_dice(map<int, ld> p, int maxd, bool add) {
    map<int, ld> newp;
    for(auto i = p.begin(); i != p.end(); i++){
        for(int j = 1; j <= maxd; j++){
            newp[i->first + j * (add? 1 : -1)] += i->second / maxd;
        }
    }
    return newp;
}

map<int, ld> dice_min(map<int, ld> p, int maxd) {
    map<int, ld> newp;
    for(auto i = p.begin(); i != p.end(); i++){
        for(int j = 1; j <= maxd; j++){
            for(int k = 1; k <= maxd; k++){
                newp[i->first + min(j, k)] += i->second / (maxd * maxd);
            }
        }
    }
    return newp;
}

map<int, ld> dice_max(map<int, ld> p, int maxd) {
    map<int, ld> newp;
    for(auto i = p.begin(); i != p.end(); i++){
        for(int j = 1; j <= maxd; j++){
            for(int k = 1; k <= maxd; k++){
                newp[i->first + max(j, k)] += i->second / (maxd * maxd);
            }
        }
    }
    return newp;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int d, m;
    cin >> d >> m;
    string adv;
    cin >> adv;
    map<int, ld> p;
    p[0] = 1;
    if(adv == "straight"){
        p = do_dice(p, 20, true);
    }
    else if(adv == "advantage") {
        p = dice_max(p, 20);
    }
    else if(adv == "disadvantage") {
        p = dice_min(p, 20);
    }
    ld ans = 0;
    //roll 20 first try
    ans += p[20];
    //immediate failure
    p[1] = 0;
    p[20] = 0;
    p = shift_prob(p, m);
    int k;
    cin >> k;
    for(int i = 0; i < k; i++){
        string s;
        cin >> s;
        bool add = s[0] == '+';
        int maxd = stoi(s.substr(2));
        p = do_dice(p, maxd, add);
    }
    for(auto i = p.begin(); i != p.end(); i++){
        if(i->first >= d) {
            ans += i->second;
        }
    }
    cout << fixed << setprecision(10) << ans << "\n";
    
    return 0;
}