#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2011 - I

//if the person can get to a cell where no mummy can get to in t turns, then the person
//is able to escape the mummies for at least t turns. 

//we can binary search across t. 

//to check if a certain t is valid, we first notice that the region of cells a person or mummy can get to
//is exactly a square of side length 2t + 1. Thus, we can use a sweepline approach to validate a given t
//in n * log(n) time. 

void insert(map<ll, ll>& m, ll val) {
    if(m.find(val) == m.end()) {
        m.insert({val, 0});
    }
    m[val] ++;
}

void erase(map<ll, ll>& m, ll val) {
    m[val] --;
    if(m[val] == 0){
        m.erase(val);
    }
}

//check if the square centered on the origin is not fully covered by the mummy squares
bool isValid(int n, vector<pair<ll, ll>>& a, ll val) {
    //for each mummy square we will keep track of either it's top or bottom, depending on if it is above
    //or below y = 0. 
    //if it's y == 0, then we can keep track of both. 
    vector<pair<ll, pair<ll, pair<ll, ll>>>> ends(0);  //x, {start / end, {top / bottom, y}}
    ends.push_back({-val, {0, {1, -1e13}}});
    ends.push_back({val, {0, {1, -1e13}}});
    map<ll, ll> top;
    map<ll, ll> bot;
    for(int i = 0; i < a.size(); i++){
        ll x = a[i].first;
        ll y = a[i].second;

        if(y >= 0){
            ends.push_back({x - val, {0, {0, y - val}}});
            ends.push_back({x + val + 1, {1, {0, y - val}}});
        }
        if(y <= 0){
            ends.push_back({x - val, {0, {1, y + val}}});
            ends.push_back({x + val + 1, {1, {1, y + val}}});
        }
    }
    sort(ends.begin(), ends.end());
    bool one_inside = false;
    bool all_covered = true;
    //cout << "SOLVING : " << val << "\n";
    //cout << "ENDS : " << "\n";
    for(int i = 0; i < ends.size(); i++){
        ll x = ends[i].first;
        bool is_start = !(ends[i].second.first);
        bool is_bot = ends[i].second.second.first;
        ll y = ends[i].second.second.second;
        //cout << x << " " << is_start << " " << is_bot << " " << y << "\n";
        if(is_bot) {
            if(is_start) {
                insert(bot, y);
            }
            else {
                erase(bot, y);
            }
        }
        else {
            if(is_start) {
                insert(top, y);
            }
            else {
                erase(top, y);
            }
        }
        if(i != ends.size() - 1 && ends[i + 1].first == x && !ends[i + 1].second.first && is_start) {
            continue;
        }
        if(-val <= x && x <= val) {
            one_inside = true;
            ll min_top = val + 1;
            ll max_bot = -val - 1;
            if(top.size() != 0){
                min_top = top.begin() -> first;
            }
            if(bot.size() != 0){
                max_bot = bot.rbegin() -> first;
            }
            //cout << "CHECKING : " << min_top << " " << max_bot << "\n";
            if(min_top - max_bot > 1){
                //cout << "FOUND NOT COVERED : " << min_top << " " << max_bot << "\n";
                all_covered = false;
            }
        }
    }
    if(one_inside && all_covered) {
        //cout << "ALL COVERED\n";
        return false;
    }
    //cout << "NOT ALL COVERED\n";
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // std::ifstream in("mummy.in");
    // std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    // std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    // std::ofstream out("mummy.out");
    // std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    // std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
    
    int n;
    cin >> n;
    int caseno = 0;
    while(n != -1){
        caseno ++;
        cout << "Case " << caseno << ": ";
        vector<pair<ll, ll>> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i].first >> a[i].second;
        }
        // if(caseno == 32) {
        //     cout << n << "\n";
        //     for(int i = 0; i < n; i++){
        //         cout << a[i].first << " "  << a[i].second << "\n";
        //     }
        // }
        ll low = 1;
        ll high = 1e12;
        ll ans = low;
        while(low <= high) {
            ll mid = low + (high - low) / 2;
            if(isValid(n, a, mid)) {
                ans = max(ans, mid);
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
        if(ans == 1e12) {
            cout << "never\n";
        }
        else {
            //perhaps if we just stand still, we might get a better outcome
            // ll stillans = 1e9;
            // for(int i = 0; i < n; i++){
            //     ll x = abs(a[i].first);
            //     ll y = abs(a[i].second);
            //     stillans = min(stillans, max(x, y));
            // }
            // ans = max(ans, stillans);
            cout << ans + 1 << "\n";
        }
        cin >> n;
    }
    
    return 0;
}
