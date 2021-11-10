
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1283E

//i don't know how this is rated for 1800, but i'll take what i can get

//first sort everyone in ascending order

//to calculate the minimum number, go from lowest to highest. Imagine that everyone got out of their houses; there are no occupied houses right now. 
//when considering someone, if there is an occupied house that they can go to, then place them there. If there is not, then place them in the greatest index
//house that you can.

//when calculating the maximum number, go from lowest to highest like before, and greedily place each person into the lowest, empty house that you can find.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end());
    int maxOccupied = 0;
    int minOccupied = 0;
    set<int> dict;
    for(int i = 0; i < n; i++){
        int next = nums[i];
        bool place = false;
        for(int j = next - 1; j <= next + 1; j++){
            if(dict.find(j) != dict.end()){
                place = true;
                break;
            }
        }
        if(!place){
            dict.insert(next + 1);
        }
    }
    minOccupied = dict.size();
    dict.clear();
    for(int i = 0; i < n; i++){
        int next = nums[i];
        for(int j = next - 1; j <= next + 1; j++){
            if(dict.find(j) == dict.end()){
                dict.insert(j);
                break;
            }
        }
    }
    maxOccupied = dict.size();
    cout << minOccupied << " " << maxOccupied << endl;

    return 0;
}



