#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1672C

//denote l as the first index where nums[i] == nums[i + 1] and r as the last index where nums[i] == nums[i + 1].

//if l and r don't exist, or l == r, then the answer is 0.

//if r - l == 1, then the answer is 1. 

//else, the answer is (r - l) - 1. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> nums(n);
        for(int i = 0; i < n; i++){
            cin >> nums[i];
        }
        int l = -1;
        int r = -1;
        for(int i = 0; i < n - 1; i++){
            if(nums[i] == nums[i + 1]){
                l = i;
                break;
            }
        }
        for(int i = n - 2; i >= 0; i--){
            if(nums[i] == nums[i + 1]){
                r = i;
                break;
            }
        }
        if(l == -1){
            cout << "0\n";
        }
        else if(r - l == 0){
            cout << "0\n";
        }
        else if(r - l == 1){
            cout << "1\n";
        }
        else{
            cout << (r - l) - 1 << endl;
        }
    }
    
    return 0;
}
