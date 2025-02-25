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

//Topcoder - 10070

//rather annoying binary search problem. Actually, it was rather annoying probably because I didn't
//entirely think through the implementation. 

//If we fix the amount of rounds, we can probably then figure out the minimum amount of troops required
//for both the wooden and stone towers such that it takes less than or equal to the fixed amount of 
//rounds to destroy all the towers. 

//Since adding more troops will only speed up the process, we can also binary search for the minimum 
//amount of troops required for some fixed amount of rounds. 

//So now we've fixed the amount of rounds and the amount of troops. How can we quickly simulate it to
//see if the actual amount of rounds is less than the fixed amount of rounds? For each tower, we can 
//compute the amount of rounds required to destroy it. 

//However, we don't want to binary search for this as this would make 3 nested binary searches. Instead,
//we can model it as a quadratic and solve the quadratic equation, saving us a factor of log(n). 

class EnemyTowers {
public:
    //finds the closest integer solution to the first positive root of ax^2 + bx + c >= 0
    //assumes the parabola is opened downwards, and there is no negative root
    //if there are no roots, returns -1
    ll quadsolve(ld a, ld b, ld c) {
        ld det = b * b - 4 * a * c;
        if(det < 0) return -1;
        ld lroot = (-b + sqrt(det)) / (2 * a);
        ld rroot = (-b - sqrt(det)) / (2 * a);
        ll sol = max((ll) ceil(lroot), 1ll);
        if(sol > rroot) return -1;
        return sol;
    }

    //given some amount of troops, how many rounds does it take?
    ll is_valid(ll h, ll a, ll w, ll n) {
        ll rcnt = 0;
        ll tothp = h * w;
        while(tothp > 0){
            ll amt = (tothp + h - 1) / h;
            ll rem = tothp - (amt - 1) * h;
            //search for amount of required turns to destroy next tower
            //rem <= n * x - a * w * (x * (x - 1)) / 2
            //(-a * w / 2) x^2 + (n + a * w / 2) x - rem >= 0
            //(-a * w) x^2 + (2n + a * w) x - 2rem >= 0
            ll x = quadsolve(-a * amt, 2 * n + a * amt, -2 * rem);
            if(x == -1) return 1e15;
            tothp -= n * x - a * amt * (x * (x - 1)) / 2;
            n -= a * amt * (x - 1);
            n -= a * ((tothp + h - 1) / h);
            rcnt += x;
        }
        return rcnt;
    }

    //given some amount of rounds, what's the minimum amount of troops
    ll calc_req(ll h, ll a, ll w, ll r) {
        ll low = 1, high = 1e10;
        ll ans = high;
        while(low <= high) {
            ll mid = low + (high - low) / 2;
            ll rounds = is_valid(h, a, w, mid);
            if(rounds <= r) high = mid - 1, ans = mid;
            else low = mid + 1;
        }
        return ans;
    }

    int attack(ll n, ll h, ll a, ll w, ll s) {
        //binary search for the amount of rounds
        ll low = 1, high = 1e9;
        ll ans = 1e9;
        while(low <= high) {
            ll mid = low + (high - low) / 2;
            ll req = calc_req(h, a, w, mid) + calc_req(h, a, s, mid);
            if(req <= n) high = mid - 1, ans = mid;
            else low = mid + 1;
        }
        return (int) (ans == 1e9? -1 : ans);
        return -1;
    }
};

int main() {
    int arg0;
    cin >> arg0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int arg1;
    cin >> arg1;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int arg2;
    cin >> arg2;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int arg3;
    cin >> arg3;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int arg4;
    cin >> arg4;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    auto c = EnemyTowers();
    int ret = c.attack(arg0, arg1, arg2, arg3, arg4);
    cout << ret;
}