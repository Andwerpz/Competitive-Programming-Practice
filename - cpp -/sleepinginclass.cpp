
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//USACO Bronze February 2022

//notice the sum of the array is guaranteed to be less than 10^6. Since we want to make the array
//into 'a' equal values, 'b', we know that the sum must be divisible by both 'a' and 'b'. 

//for each divisor of the sum, test whether or not it is a valid 'b' value. This can be tested in
//linear time.

bool isValid(vector<int> nums, int a){
    int sum = 0;
    for(int i = 0; i < nums.size(); i++){
        sum += nums[i];
        if(sum == a){
            sum = 0;
        }
        else if(sum > a){
            return false;
        }
    }
    return sum == 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> nums(n, 0);
        int sum = 0;
        for(int i = 0; i < n; i++){
            cin >> nums[i];
            sum += nums[i];
        }
        if(sum == 0){
            cout << "0\n";
            continue;
        }
        int ans = -1;
        for(int i = 1; i <= sum; i++){
            if(sum % i == 0 && isValid(nums, i)){
                ans = n - (sum / i);
                break;
            }
        }
        cout << ans << endl;
    }
    
    return 0;
}
