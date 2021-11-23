
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//Codeforces - 1612B

//you can pretty much simulate the problem.

//start with the left side. You can make arr[0] = a, and greedily pick from the highest numbers available. If the next available number
//is lower than a, then the input is invalid. 

//same deal with the right side, make arr[n - 1] = b, and pick from the lowest numbers. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, a, b;
        cin >> n >> a >> b;
        a --;
        b --;
        vector<int> nums(n);
        vector<bool> v(n);
        v[a] = true;    nums[0] = a + 1;
        v[b] = true;    nums[n - 1] = b + 1;
        int high = n - 1;
        int low = 0;
        bool isValid = true;
        for(int i = 1; i < n - 1; i++){
            if(i < n / 2){
                while(v[high]){
                    high --;
                    if(high < a){
                        isValid = false;
                        goto outer;
                    }
                }
                v[high] = true;
                nums[i] = high + 1;
            }
            else{
                while(v[low]){
                    low ++;
                    if(low > b){
                        isValid = false;
                        goto outer;
                    }
                }
                v[low] = true;
                nums[i] = low + 1;
            }
        }
        outer: ;
        if(isValid){
            for(int i : nums){
                cout << i << " ";
            }
            cout << endl;
        }
        else{
            cout << "-1\n";
        }
    }
    
    return 0;
}
