#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSES 1644

//A variation on the maximum subarray sum problem. In that problem, for a given pfx, pfx[r], you want to find the minimum
//pfx, pfx[l] before it to get the maximum subarray sum ending at r. 

//in this problem, the search range is restricted to [r - b, r - a]. I used a min range query segtree to search for min along
//that range. 

//range min query tree
const int N = 3e5;  //limit for segtree size
int tn;
ll t[2 * N];

void modify(int p, ll value) { // set value at position p
    p += tn;
    t[p] = value;
    for (p /= 2; p > 0; p /= 2) {
        t[p] = min(t[p * 2], t[p * 2 + 1]);
    }
}

ll query(int l, int r) { // min on interval [l, r)
    ll res = 1e18;
    for (l += tn, r += tn; l < r; l /= 2, r /= 2) {
        if (l % 2 == 1) {
            res = std::min(res, t[l]);
            l++;
        }
        if (r % 2 == 1) {
            r--;
            res = std::min(res, t[r]);
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, a, b;
    cin >> n >> a >> b;
    tn = n + 1;
    ll sum = 0;
    ll ans = -1e18;
    for(int i = 0; i < n; i++){
        ll next;
        cin >> next;
        sum += next;
        //cout << i - b + 1<< " " << i - a + 2 << "\n";
        //cout << query(i, i + 1) << "\n";
        //cout << query(max(i + 1 - b, 0), max(i - a + 2, 0)) << "\n";
        if(i + 1 >= a) {
            ans = max(ans, sum - query(max(i + 1 - b, 0), max(i - a + 2, 0)));
        }
        modify(i + 1, sum);
    }
    cout << ans << "\n";
    
    return 0;
}
