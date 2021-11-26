
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//USACO - 2021 US Open Silver 3 - Do you know your ABC's

//it seems my double heap's permutation algorithm method would have worked, if I had used a better way to check for duplicate triples. 

//for this solution, the first step is noticing that any valid abc is only one subtraction operation from any of the initially 
//provided numbers. 

//we can then just generate all possible valid abcs, and then test them every possible combination. 

struct Triple {
    int x, y, z;

    Triple(int x, int y, int z){
        this->x = x;
        this->y = y;
        this->z = z;
    }
    bool operator<(const Triple b) const
    {
    return x > b.x;
    }
};

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
        set<int> possibleNums;
        for(int i : nums){
            possibleNums.insert(i);
            for(int j : nums){
                if(i - j > 0){
                    possibleNums.insert(i - j);
                }
            }
        }
        int ans = 0;
        for(int i : possibleNums){
            for(int j : possibleNums){
                for(int k : possibleNums){
                    if(i <= j && j <= k){
                        bool isValid = true;
                        set<int> curSet = {i, j, k, i + j, j + k, k + i, i + j + k};
                        for(int a : nums){
                            if(curSet.find(a) == curSet.end()){
                                isValid = false;
                                break;
                            }
                        }
                        if(isValid){
                            ans ++;
                        }
                        
                    }
                }
            }
        }
        cout << ans << endl;
    }
    
    return 0;
}
