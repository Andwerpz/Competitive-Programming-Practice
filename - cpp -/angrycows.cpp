
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//USACO Silver January 2016

//binary search across all values of R. We can use greedy algorithm to confirm.

bool isValid(vector<int> nums, int k, int radius){
    int max = -1;
    int numLeft = k;
    for(int i = 0; i < nums.size(); i++){
        if(nums[i] > max){
            max = nums[i] + radius * 2;
            numLeft --;
        }
    }
    return numLeft >= 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("angry.in", "r", stdin);
	freopen("angry.out", "w", stdout);
    
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end(), [] (int a, int b) {return a < b;});
    int low = 0;
    int high = 1e9;
    int mid = low + (high - low) / 2;
    int ans = 1e9;
    while(low <= high){
        if(isValid(nums, k, mid)){
            ans = min(ans, mid);
            high = mid - 1;
        }
        else{
            low = mid + 1;
        }
        mid = low + (high - low) / 2;
    }
    cout << ans << endl;
    
    return 0;
}
