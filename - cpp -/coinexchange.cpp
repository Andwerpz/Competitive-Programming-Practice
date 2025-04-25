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

//University of Alberta Programming Contest 2025 Open - J

//if you stare at the exchange rates for a while, you might notice some stuff.

//first, it's always best to directly convert A into C, as converting A into B then C is 3 times as wasteful. 

//Then, B -> E -> D -> B actually produces more B than it takes, however you're limited by X, the amount of times you 
//can do the D -> B transformation. So if you put 9 B in, then it'll consume 4 X and produce 12 B with no other residue. 

//look at the code for more details. 

ll a, b, c, d, e, x;
void etod() {
    d += (e / 3) * 2;
    e %= 3;
}

void dtob() {
    ll amt = min(x, d / 2);
    d -= amt * 2;
    b += amt * 3;
    x -= amt;
}

void btoe1() {
    if(b < 3) return;
    e += 4;
    b -= 3;
}

void btoen(ll n) {
    if(b < 3 * n) return;
    e += 4 * n;
    b -= 3 * n;
}

void glitch1() {
    // cout << "G1 : " << b << endl;
    btoe1();
    etod();
    dtob();
}

void glitchn(int n) {
    btoen(n);
    etod();
    dtob();
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> a >> b >> c >> d >> e >> x;
    //convert all a into c, then remaining a into b
    c += a / 5;
    a %= 5;
    b += a / 3;
    a %= 3;
    //convert e into d
    etod();
    //convert d into b 
    dtob();
    //do single glitches until x runs out, or b >= 9
    while(b < 9 && x > 0) glitch1();
    //if b >= 9, then we can do infinite coins glitch
    if(b >= 9) {
        ll bamt = (x / 4);
        x -= bamt * 4;
        b += bamt * 3;
        // cout << "GN : " << endl;
        // glitchn((x / 4) * 3);
    }
    // cout << "FX : " << x << endl;
    while(x != 0) glitch1();
    //convert b into c
    c += b / 3;
    cout << c << "\n";

    return 0;
}