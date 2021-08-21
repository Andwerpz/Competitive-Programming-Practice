
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

//CSES - Missing Number

int main()
{
    
    int n;
    cin >> n;
    vector<int> nums(n, 1000000);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end());
    for(int i = 0; i < n; i++){
        if(i + 1 != nums[i]){
            cout << i + 1 << "\n";
            break;
        }
    }

    return 0;
}



