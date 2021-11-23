
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//Codeforces - 1610B

//first, do a regular check to see if the array is palindromic: high and low pointers, ect.
//if at any point, nums[high] != nums[low], then you know that if the array is kalindromic, then you can delete all occurrences of 
//one of them, and the array will become a palindrome. 

//so just do a check for both values, and if the array becomes a palindrome, then it is kalindromic. 

bool check(int del, vector<int> nums){
    int high = nums.size() - 1;
    int low = 0;
    while(true){
        while(nums[high] == del){
            high --;
        }
        while(nums[low] == del){
            low ++;
        }
        if(low > high){
            break;
        }
        if(nums[high] != nums[low]){
            return false;
        }
        high --;
        low ++;
    }
    return true;
}

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
        int high = n - 1;
        int low = 0;
        int a = 0;
        int b = 0;
        bool isValid = true;
        while(true){
            if(low > high){
                break;
            }
            if(nums[high] != nums[low]){
                isValid = false;
                a = nums[high];
                b = nums[low];
                break;
            }
            high --;
            low ++;
        }
        if(isValid){
            cout << "YES\n";
            continue;
        }
        cout << ((check(a, nums) || check(b, nums))? "YES\n" : "NO\n");
    }
    
    return 0;
}
