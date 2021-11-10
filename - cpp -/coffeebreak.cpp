
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1041C

//solved in java

using namespace std;

int main() {

    int n, m, d;
    cin >> n >> m >> d;
    set<int> nums;
    vector<int> order(n);
    for(int i = 0; i < n; i++){
        int temp;
        cin >> temp;
        order[i] = temp;
        nums.insert(temp);
    }
    map<int, int> dict;
    int ans = 0;
    while(nums.size() != 0){
        ans ++;
        int pointer = 0;
        auto next = nums.upper_bound(pointer);
        while(next > pointer){

        }
    }

    return 0;
}



