#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

// ICPC PACNW 2025 - E

//first, should probably work some examples to get an intuition as to how the fractal drawing works. 
//my intuition is that it's like the turtle drawing programs. At each step, we can choose to either go 
//along B or C, and then the entire scale changes according to the ratio between A and whatever segment we chose.

//first, observe that if one of B or C is larger than A, then the length of the segments is unbounded
//next, if both segments are smaller than A, it must be bounded as we are decreasing our travel length every step. 

//next, suppose that both segments have equal length to A. I could not prove this, but I guessed that 
//this case is unbounded. 

//finally, we have the case where is shorter than A, and one is the same length. If the same length one is exactly aligned with A
//then it's unbounded, otherwise it's bounded. The intution here is that if the same length one is not aligned, you'll
//be travelling in a big circle. 

ll dist_sq(pair<ll, ll> a, pair<ll, ll> b){
    return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

pair<ll, ll> sub(pll a, pll b) {
    return {a.first - b.first, a.second - b.second};
}

pll add(pll a, pll b) {
    return {a.first + b.first, a.second + b.second};
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while(t--){
        pll p0, p1, p2;
        cin >> p0.first >> p0.second >> p1.first >> p1.second >> p2.first >> p2.second;
        ll dA = dist_sq({0, 0}, p0);
        ll dB = dist_sq(p0, p1);
        ll dC = dist_sq(p0, p2);
        if(max(dC, dB) > dA) {
            cout << "NO\n";
            continue;
        }
        if(min(dC, dB) < dA) {
            if(dA == dB && (p0 == sub(p1, p0))) {
                cout << "NO\n";
                continue;
            }
            else if(dA == dC && (p0 == sub(p2, p0))) {
                cout << "NO\n";
                continue;
            }
            cout << "YES\n";
            continue;
        }
        assert(dA == dB && dA == dC);
        cout << "NO\n";
    }

    return 0;
}