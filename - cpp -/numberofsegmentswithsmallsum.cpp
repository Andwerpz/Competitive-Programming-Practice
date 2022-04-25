#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces 307093C

//for each index i, figure out the largest subarray starting at i that we can make
//with sum less than s.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    ll s;
    cin >> n >> s;
    vector<int> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    ll ans = 0;
    int j = 0;
    ll sum = 0;
    for(int i = 0; i < n; i++){
        while(j < n && sum + nums[j] <= s){
            sum += nums[j];
            j ++;
        }
        ans += j - i;
        sum -= nums[i];
    }
    cout << ans << endl;
    
    return 0;
}
