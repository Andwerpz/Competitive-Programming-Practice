
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1338A

//just try out every value of x starting from 1 to see if it's valid or not. 

//because you're effectively adding bits, on the xth time, you can choose any number from 0 - (2^x - 1) to add to each value. 

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<ll> nums(n);
        for(int i = 0; i < n; i++){
            cin >> nums[i];
        }
        bool isValid = true;
        ll sum = 0;
        int x = 0;
        for(int i = 1; i < n; i++){
            if(nums[i - 1] > nums[i]) {
                isValid = false;
                break;
            }
        }
        while(!isValid){
            x ++;
            sum += (ll) pow(2, x - 1);
            isValid = true;
            ll low = nums[0];
            for(int i = 1; i < n; i++){
                ll nextLow = nums[i];
                ll nextHigh = nums[i] + sum;
                if(nextHigh < low){
                    isValid = false;
                    break;
                }
                low = max(low, nextLow);
            }
        }
        cout << x << endl;
    }

    return 0;
}



