
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

//1496B - Max and Mex

//notice that if the mex is less than the max, then the value added to the set will never change the mex, since the new value is guaranteed to be higher than the mex.
//in this case, if the new value is not included in the set, then the final answer will be n + 1, else it will be n.

//if the mex is greater than the maximum value, then the new value generated will always be equal to mex, therefore, in the next operation, the mex and max will each be 1
//unit higher, making a cycle. The answer in this case is going to be n + k.

int main()
{
    
    int t, n, k;
    
    cin >> t;
    
    while(t-- > 0){
        cin >> n >> k;
        vector<int> nums;
        for(int i = 0; i < n; i++){
            int temp;
            cin >> temp;
            nums.push_back(temp);
        }
        sort(nums.begin(), nums.end());
        bool mexmax = true;
        int mex = 0;
        int max = nums[n - 1];
        for(int i = 0; i < n; i++){
            if(nums[i] != i){
                mexmax = false;
                mex = i;
                break;
            }
        }
        if(mexmax){
            cout << n + k << "\n";
        }
        else{
            int sum = max + mex;
            int nextVal = (max + mex) / 2 + (sum % 2 == 1? 1 : 0);
            bool contains = false;
            for(int i = 0; i < n; i++){
                if(nums[i] == nextVal){
                    contains = true;
                    break;
                }
            }
            if(k == 0){
                contains = true;
            }
            cout << n + (contains? 0 : 1) << "\n";
        }
    }
    
    return 0;
}

