#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

// ICPC PACNW 2025 - C

//the three conditions on the pictures just mean that every possible subarray of blobs are captured in some photo. 
//so we just need to compute the sum of scores over all subarrays. 

//suppose that we compute the score for all subarrays that have a given right boundary R. 
//we notice that as we decrease L, the score of the subarray will monotonically decrease. 
//this is because smaller 'same color differences' trump larger ones, and we can only add more smaller 
//differences the larger we make the subarray. 

//we can characterize each 'color difference' segment by what L value will fully contain it for a given R. 
//then notice that for all 'active' color difference segments, as the L value decreases, the segment length will also
//decrease. So we can just keep a monotonic stack of active segments. 

//then, to increment R, we just have to add the one new segment that gets added to our stack, kicking out any segments
//that the new segment makes inactive, or maybe the new segment is already inactive as it's too big. 

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vi a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) {
        a[i] --;
    }
    vi occ(n, -1);
    stack<array<ll, 3>> s;   //{ind, sz, dtonext}
    ll ans = 0;
    ll sum = 0;
    for(int i = 0; i < n; i++) {
        int val = a[i];
        // cout << "I : " << i << " " << val << endl;
        if(occ[val] != -1) {
            ll csz = i - occ[val];
            ll cind = occ[val];
            while(s.size() != 0 && s.top()[0] < cind) {
                if(s.top()[1] >= csz) {
                    sum -= s.top()[2] * s.top()[1];
                    s.pop();
                }
                else {
                    break;
                }
            }
            // cout << "HERE" << endl;
            assert(s.size() == 0 || s.top()[1] < csz);
            if(s.size() != 0 && s.top()[0] > cind) {
                //this segment already overridden
            }
            else {
                ll cdton;
                if(s.size() == 0) cdton = cind + 1;
                else cdton = cind - s.top()[0];
                // cout << "HERE : " << cdton << endl;
                sum += cdton * csz;
                s.push({cind, csz, cdton});
            }
        }
        ans += sum;
        occ[val] = i;
    }
    cout << ans << "\n";

    return 0;
}