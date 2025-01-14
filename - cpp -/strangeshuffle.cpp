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

//Codeforces - 1470C

//first, we can try to evolve some sample cases to see what goes on. 
//after q queries, there are q elements after the impostor that are > k, and q elements behind
//the impostor that are < k (given that n is large enough). Crucially, the impostor always remains
//equal to k. 
//So my solution idea is to find some index on the left and right side of the impostor, and then 
//binary search for the location of the impostor. 

//We can spend 700 queries to find indices to the left and right. 350 queries we'll just spend to evolve
//the state, and another 350 we'll query with interval n / 350 to find indices with values < and > k. 
//Since n is at most 10^5, this guarantees that we'll find something < and > k. 

//Then, we can simply binary search for the impostor location. We have 300 queries remaining, which 
//is more than enough. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    int qamt = 350;
    //queries to evolve state
    for(int i = 0; i < qamt; i++){
        cout << "? 1" << endl;
        int tmp;
        cin >> tmp;
    }
    //queries to find elements above and below k
    int l = -1, r = -1;
    for(int i = 0; i < qamt; i++){
        int ind = n * i / qamt;
        cout << "? " << ind + 1 << endl;
        int tmp;
        cin >> tmp;
        if(tmp < k) l = ind;
        if(tmp > k) r = ind;
    }
    if(l == -1 || r == -1) {
        cout << "! 1" << endl;
        return 0;
    }
    //binary search for impostor
    if(r < l) r += n;
    int ans = -1;
    while(ans == -1){
        int mid = l + (r - l) / 2;
        cout << "? " << (mid % n) + 1 << endl;
        int tmp;
        cin >> tmp;
        if(tmp == k) ans = mid % n;
        if(tmp < k) l = mid + 1;
        if(tmp > k) r = mid - 1;
    }
    cout << "! " << ans + 1 << endl;
    
    return 0;
}