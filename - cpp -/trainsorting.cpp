#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Kattis - trainsorting

//we can pick a center, and place all cars below it to the left, and all cars above to the 
//right. 

//to determine the maximum amount of cars to the left and right, we use LIS. Since there aren't 
//that many cars, we can get away with naively doing LIS on the left and right for every
//choice of center. 

int calc_lis(vector<int>& a) {
    vector<int> b(a.size() + 1, 1e9);
    b[0] = 0;
    int ans = 0;
    for(int i = 0; i < a.size(); i++){
        if(a[i] == -1){
            continue;
        }
        int low = 0;
        int high = b.size() - 1;
        int ind = high;
        while(low <= high) {
            int mid = low + (high - low) / 2;
            if(b[mid] >= a[i]) {
                ind = min(ind, mid);
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }
        ans = max(ans, ind);
        b[ind] = min(b[ind], a[i]);
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<int> inc(n, -1), dec(n, -1);
    for(int i = 0; i < n; i++){
        inc[i] = a[i];
    }
    priority_queue<pair<int, int>> q;
    for(int i = 0; i < n; i++){
        q.push({-a[i], i});
    }
    int ans = calc_lis(inc) + calc_lis(dec);
    while(q.size() != 0){
        int ind = q.top().second;
        q.pop();
        dec[ind] = 1e6 - inc[ind];
        inc[ind] = -1;
        ans = max(ans, calc_lis(inc) + calc_lis(dec));
    }
    cout << ans << "\n";
    
    return 0;
}
