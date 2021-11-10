
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1340A

//you just have to notice something about the generator. Once the first number is placed, then all the other numbers will start going right after it, until there is no more room
//then the second string of numbers will be placed, then the third. You just have to check that if a pair of numbers increase, then the increase is only 1

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
        }
        bool isValid = true;
        for(int i = 1; i < n; i++){
            int prev = nums[i - 1];
            int next = nums[i];
            if(next > prev && next - 1 != prev){
                isValid = false;
                break;
            }
        }
        cout << (isValid? "Yes\n" : "No\n");
    }

    return 0;
}



