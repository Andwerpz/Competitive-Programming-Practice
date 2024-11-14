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

//Meta Hacker Cup 2024 Round 3 - C

//let A be the amount of coins that we're missing. For a given A, observe that we only need to solve for D
//locally, as our choice of D doesn't affect our subsequent choices beyond lowering the EV to get to A - 1
//missing coins. 

//so for given A and D, the EV number of money spent is D / (X + (1 - X) * A / N), where X = min((D - 1) * P, 1).

//Next thing to observe is that as A decreases, the optimal value for D will increase. This idea will form our
//solution: we'll iterate across D, and for each D, binary search for the next A in which D + 1 is a better value
//for D. 

//Now we know D, and a range of A for which this D is optimal. The final problem is how we're going to sum the
//values. Since an exact solution is difficult, we can get away with an approximation. There are three cases:

//D = 1 : in this case, X = 0, and the EV is 1 / (A / N), or N * (1 / A). This is simply a section of the harmonic
//  series. Luckily, euler already figured this one out: H_n = ln(n) + \gamma, and the error is small for sufficiently
//  large n. So we can just precompute the first million terms of H_n, and use the approximation for higher n. 
//X = 1 (D is sufficiently large to guarantee the new coin) : In this case, the EV is just D. no approximation needed
//other : We'll really have to approximate here. We can simply cut this range into 1e8 chunks, and just take a riemann
//  sum. Use the trapezoidal approximation if you wish. 

vd H;
void init_H() {
    H = vd(100000000);
    H[0] = 0;
    for(int i = 1; i < H.size(); i++){
        H[i] = H[i - 1] + (ld) 1.0 / (ld) i;
    }
}

//harmonic series approximation
//H_n = ln(n) + \gamma
ld calc_H(ll n) {
    if(n < H.size()) {
        return H[n];
    }
    return log(n) + 0.57721566490153286060651;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ifstream in("--in--.txt");
    streambuf *cinbuf = cin.rdbuf(); //save old buf
    cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    ofstream out("--out--.txt");
    streambuf *coutbuf = cout.rdbuf(); //save old buf
    cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

    init_H();
    int t;
    cin >> t;
    int casi = 0;
    while(t--){
        casi ++;
        ll n;
        ld p;
        cin >> n >> p;
        ll inc = max(1ll, (ll) (n / 1e8));
        p /= 100;
        ll a = n;   //nr coins missing
        int d = 1;
        ld ans = 0;
        for(int d = 1; d <= 101; d++){
            if(a == 0){
                break;
            }
            //binary search for when d + 1 is better than d
            ll low = 0;
            ll high = a;
            ll na = low;
            while(low <= high){
                ll mid = low + (high - low) / 2;
                ld x1 = min((d - 1) * p, (ld) 1.0);
                ld x2 = min(d * p, (ld) 1.0);
                ld cev = (ld) d / (x1 + (1.0 - x1) * ((ld) mid / (ld) n));
                ld nev = (ld) (d + 1) / (x2 + (1.0 - x2) * ((ld) mid / (ld) n));
                if(cev > nev) {
                    na = mid;
                    low = mid + 1;
                }
                else {
                    high = mid - 1;
                }
            }
            if(a == na){
                continue;
            }
            //update ans using current d    
            //how to do summation quickly? just approximate??
            ld x = min((d - 1) * p, (ld) 1.0);
            if(d == 1){
                //harmonic series approximation
                ans += n * (calc_H(n) - calc_H(na));
                a = na;
            }
            else if(x != 1.0){
                //trapezoidal approximation
                while(a != na) {
                    ll cna = max(na, a - inc);
                    ll mid = a - (a - cna) / 2;
                    ld evl = (ld) d / (x + (1.0 - x) * ((ld) a / (ld) n));
                    ld evr = (ld) d / (x + (1.0 - x) * ((ld) (cna + 1) / (ld) n));
                    ld ev = (ld) d / (x + (1.0 - x) * ((ld) mid / (ld) n));
                    ans += ev * (a - cna);
                    a = cna;
                }
            }
            else {
                //no approximation needed
                ans += (ld) d * (ld) a;
                break;
            }
        }
        cout << fixed << setprecision(10) << "Case #" << casi << ": " << ans << "\n";
    }
    
    return 0;
}