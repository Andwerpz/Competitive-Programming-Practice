
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1283C

//if you make the list into a permuation from 1 - n, with the extra condition that the value at index i must not equal to i, then you have a valid
//set of gifts. 

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
        nums[i] --;
    }
    set<int> missing;
    for(int i = 0; i < n; i++){
        missing.insert(i);
    }
    for(int i = 0; i < n; i++){
        if(missing.find(nums[i]) != missing.end()){
            missing.erase(nums[i]);
        }
    }
    for(int i = 0; i < n; i++){
        if(nums[i] == -1 && missing.find(i) != missing.end()){
            set<int>::iterator it = missing.end();
            it --;
            if(*it == i){
                it --;
            }
            nums[i] = *it;
            missing.erase(*it);
        }
    }
    for(int i = 0; i < n; i++){
        if(nums[i] == -1){
            set<int>::iterator it = missing.end();
            it --;
            nums[i] = *it;
            missing.erase(*it);
        }
    }
    for(int i = 0; i < n; i++){
        cout << (nums[i] + 1) << " ";
    }
    cout << endl;

    return 0;
}



