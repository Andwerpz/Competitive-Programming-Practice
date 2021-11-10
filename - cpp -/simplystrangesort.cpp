
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1561A

//just simulate the problem statement; you have enough time.

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
        for(int i = 0; i < n; i++){
            cin >> nums[i];
            nums[i] --;
        }
        int ans = 0;
        int counter = 1;
        bool sorted = false;
        while(true){
            sorted = true;
            for(int i = 0; i < n; i++){
                if(nums[i] != i){
                    sorted = false;
                    break;
                }
            }
            if(sorted){
                cout << ans << endl;
                break;
            }
            if(counter % 2 == 1){
                int pointer = 0;
                while(pointer < n - 2){
                    if(nums[pointer] > nums[pointer + 1]){
                        int temp = nums[pointer];
                        nums[pointer] = nums[pointer + 1];
                        nums[pointer + 1] = temp;
                    }
                    pointer += 2;
                }
            }
            else {
                int pointer = 1;
                while(pointer < n - 1){
                    if(nums[pointer] > nums[pointer + 1]){
                        int temp = nums[pointer];
                        nums[pointer] = nums[pointer + 1];
                        nums[pointer + 1] = temp;
                    }
                    pointer += 2;
                }
            }
            ans ++;
            counter ++;
        }
    }

    return 0;
}



