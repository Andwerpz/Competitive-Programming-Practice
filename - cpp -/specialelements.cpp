
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1352E

//don't let the tight time and mem limits scare you, trust in the power of c++

//you just have to do a O(n^2) solution. For each number, just do a two pointer check to see whether it is special or not.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> nums(n);
        int ans = 0;
        for(int i = 0; i < n; i++){
            cin >> nums[i];
        }
        for(int i = 0; i < n; i++){
            int cur = nums[i];
            int pointer = 0;
            int sum = nums[0];
            for(int j = 1; j < n; j++){
                sum += nums[j];
                while(pointer != n && j - pointer > 1 && sum - nums[pointer] >= cur){
                    sum -= nums[pointer];
                    pointer ++;
                }
                if(sum == cur){
                    ans ++;
                    break;
                }
            }
        }
        cout << ans << endl;
    }

    return 0;
}



