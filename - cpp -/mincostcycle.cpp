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

//AtCoder - AGC28C

//instead of assigning each edge the weight of min(a_x, b_y), we'll instead pick the weight between a_x and b_y for each edge. 
//the key idea is that the answer this way will never be less than the answer for the actual problem. 

//Classify the nodes into 4 categories:
//1. all outgoing weights = a_i, all incoming weights = b_i
//2. no outgoing weights = a_i, no incoming weights = b_i
//3. all outgoing weights = a_i, no incoming weights = b_i
//4. no outgoing weights = a_i, all incoming weights = b_i

//We just need to assign each node a category, and then we'll get an answer as long as our assignment is valid. 
//Two trivial assignments are assigning every node to category 3, and assigning everything to category 4. 
//If we don't assign everything to 3 or 4, then we need to have at least one node in both categories 1 and 2. 

//Computing the answer for trivial assignments is trivial. For the non-trivial assignment, we can first sort all the a_i and b_i
//together in ascending order. If there exists a node with both a_i and b_i in the first n smallest edge weights, then we can 
//just take the n smallest weights as our answer. Otherwise, all n nodes have one of a_i or b_i in the first n weights.
//In this case, we need to deselect one of the first n weights, and select the next greatest weight to ensure that
//at least one node has 2 weights selected. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    ll ans = 1e18;
    ll asum = 0, bsum = 0;
    vector<pll> a(n * 2);
    for(int i = 0; i < n; i++){
        cin >> a[i * 2 + 0].first >> a[i * 2 + 1].first;
        a[i * 2 + 0].second = i, a[i * 2 + 1].second = -i;
        asum += a[i * 2 + 0].first;
        bsum += a[i * 2 + 1].first;
    }
    if(n == 1) {
        cout << "0\n";
        return 0;
    }
    ans = min(ans, min(asum, bsum));
    ll sum = 0, cnt = 0;
    sort(a.begin(), a.end());
    set<int> s;
    for(int i = 0; i < n; i++){
        s.insert(abs(a[i].second));
        sum += a[i].first;
    }
    if(s.size() == n){
        for(int i = 0; i < n; i++){
            if(abs(a[n].second) == abs(a[i].second)) {
                ans = min(ans, sum - a[i].first + a[n + 1].first);
            }
            else {
                ans = min(ans, sum - a[i].first + a[n].first);
            }
        }
    }
    else {
        ans = min(ans, sum);
    }
    cout << ans << "\n";
    
    return 0;
}