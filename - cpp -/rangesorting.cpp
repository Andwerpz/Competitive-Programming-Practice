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

//Codeforces - 1827 B1, B2

//tricky monotonic stack problem. 

//first, note that if we apply any overlapping operations, they can always be combined for less or equal
//cost. Next, for a given triple (l, k, r), there should not be an operation that goes across index k
//to k + 1 if max([l, k]) < min([k + 1, r]), as sorting the two segments independently is sufficient. 

//finally, note that the total cost of sorting a subarray [l, r] is simply the size of the subarray, 
//(r - l + 1) minus the amount of operations that we can split the subarray into. So if we can count the 
//number of operations we'll perform across all subarrays, then we can subtract it from the total
//length of all subarrays and that's our answer. 

//Since each operation must have a minimum element, it might be useful to count for each element a[i],
//how many subarrays have an operation where a[i] is the minimum element. Let rpos[i] be the index of
//the first element after i that is greater than a[i]. Note that for a[i] to be part of a minimum operation,
//i <= r < rpos[i] must be true. This means that all the elements in range [i + 1, r] must be greater than
//a[i]. 

//The left bound is more complicated. let kpos[i] be the greatest value such that kpos[i] < i and 
//a[kpos[i]] < a[i]. Also let xpos[i] be greatest value such that xpos[i] < kpos[i] and a[xpos[i]] > a[i]. 
//I also claim that xpos[i] < l <= i must be true as well. So as long as xpos[i] < l <= i and i <= r < rpos[i]
//are true, then the segment [l, r] will have a[i] as a minimum element in an operation. So for a given i, 
//there are (i - xpos[i]) * (rpos[i] - i) operations that have a[i] as minimum. 

//rpos can be easily found using monotonic stack, but xpos is much more tricky. We can use 2 monotonic stacks 
//for finding xpos, s1 will be monotonically decreasing, and s2 increasing. The idea is that s1 will be responsible
//for finding kpos, and s2 will find xpos. We'll iterate through a from n -> 1. When considering a[i], we'll first check
//if it can be a valid x value by looking inside s2 and removing any elements that are less than it. Then we'll
//check if it can be a valid k value by looking inside s1 and removing any elements larger than it, and moving
//them to s2. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int t;
    cin >> t;
    while(t--){
        ll n;
        cin >> n;
        vi a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vl xpos(n, -1), rpos(n, n);
        //for every i, compute the last x where x < k and a[x] > a[i]. 
        //k is last k where k < i and a[k] < a[i]
        stack<pii> s1, s2;  //dec, inc
        for(int i = n - 1; i >= 0; i--){
            while(s2.size() && s2.top().first < a[i]) {
                xpos[s2.top().second] = i;
                s2.pop();
            }
            while(s1.size() && s1.top().first > a[i]) {
                s2.push(s1.top());
                s1.pop();
            }
            rpos[i] = s1.size()? s1.top().second : n;
            s1.push({a[i], i});
        }
        ll ans = n * (n + 1) * (n + 2) / 6; //total sum over all subarrays. 
        for(int i = 0; i < n; i++){
            //how many times is this the minimum of a operation
            ans -= (i - xpos[i]) * (rpos[i] - i);
        }
        cout << ans << "\n";
    }
    
    return 0;
}