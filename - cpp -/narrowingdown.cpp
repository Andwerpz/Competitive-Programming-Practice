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

//Meta Hacker Cup 2025 Round 1 - C

//observe that it's possible to reduce a segment to 0 iff the xor sum of the segment is 0. 

//if within a reducible segment, there is a subsegment such that the xor sum is 0, then that saves
//us an operation. Then the cost of a reducible segment is just the length of the segment minus
//the maximum amount of segments that we can partition it into such that each partition has xor sum of 0.

//we'll start with the maximum cost, and then subtract costs when we see that we can get a subsegment
//with xor sum 0. We can keep a map that stores a frequency of prefix xor sums to do this. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ifstream in("narrowing_down_input.txt");
    streambuf *cinbuf = cin.rdbuf(); //save old buf
    cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    ofstream out("--out--.txt");
    streambuf *coutbuf = cout.rdbuf(); //save old buf
    cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
    
    int t;
    cin >> t;
    int casi = 0;
    while(t--) {
        casi ++;
        ll n;
        cin >> n;
        vi a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        map<int, ll> fm; //sum of array begins, amt of array begins
        int xsum = 0;
        ll ans = 0;
        for(int i = 0; i < n; i++) {
            ll cur = n - i;
            ans += cur * (cur + 1) / 2;
        }
        fm[0] ++;
        for(int i = 0; i < n; i++) {
            xsum ^= a[i];
            ll f = fm[xsum];
            // cout << "DEC : " << i << " " << (f * (f + 1) / 2) << "\n";
            ans -= f * (f + 1) / 2;
            fm[xsum] ++;
        }
        cout << "Case #" << casi << ": " << ans << "\n";
    }
    
    return 0;
}