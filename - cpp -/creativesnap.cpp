#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1111C

//just implement the recursive algorithm described in the problem statement. 

//returns the number of elements that are less than or equal to val
int do_search(vector<int>& a, int val) {
    if(a[a.size() - 1] <= val) {
        return a.size();
    }
    int low = 0;
    int high = a.size() - 1;
    int ans = high;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(a[mid] > val) {
            ans = min(ans, mid);
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    return ans;
}

ll solve(int l, int r, ll A, ll B, vector<int>& a) {
    //find how many avengers are inside the range
    ll acnt = do_search(a, r - 1) - do_search(a, l - 1);
    if(acnt == 0){
        return A;
    }
    ll ans = B * acnt * (r - l);
    int mid = l + (r - l) / 2;
    if(l + 1 != r){
        ans = min(solve(l, mid, A, B, a) + solve(mid, r, A, B, a), ans);
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n, k, A, B;
    cin >> n >> k >> A >> B;
    vector<int> a(k);
    for(int i = 0; i < k; i++){
        cin >> a[i];
        a[i] --;
    }
    sort(a.begin(), a.end());
    cout << solve(0, (1 << n), A, B, a) << "\n";
    
    return 0;
}