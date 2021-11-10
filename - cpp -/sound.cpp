
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//DMOJ - btoi07p3

//just use two pointers maximum and minimum technique. 

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, c;
    cin >> n >> m >> c;
    //two pointers, two stack
    vector<int> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    stack<int> pfxMax;
    stack<int> pfxMin;
    stack<int> first;
    int max = -1;
    int min = 1000001;
    for(int i = 0; i < std::min(m, n); i++){
        first.push(nums[i]);
        max = std::max(max, nums[i]);
        min = std::min(min, nums[i]);
    }
    bool valid = false;
    //cout << max << " " << min << endl;
    string ans = "";
    if(max - min <= c){
        valid = true;
        ans.append(to_string(1) + "\n");
    }
    for(int i = m; i < n; i++){
        //cout << "I: " << i << endl;
        //cout <<  pfxMax.size() << " " << pfxMin.size() << " " << firstMax.size() << endl;
        if(pfxMax.size() == 0){
            max = -1;
            min = 1000001;
            int tMax = -1; int tMin = 1000001;
            while(first.size() != 0){
                tMax = std::max(first.top(), tMax); tMin = std::min(first.top(), tMin);
                pfxMax.push(tMax); pfxMin.push(tMin);
                first.pop();
            }
        }
        pfxMax.pop();
        pfxMin.pop();
        first.push(nums[i]);
        max = std::max(max, nums[i]);
        min = std::min(min, nums[i]);
        if(pfxMax.size() == 0){
            max = -1;
            min = 1000001;
            int tMax = -1; int tMin = 1000001;
            while(first.size() != 0){
                tMax = std::max(first.top(), tMax); tMin = std::min(first.top(), tMin);
                pfxMax.push(tMax); pfxMin.push(tMin);
                first.pop();
            }
        }
        int curMax = std::max(max, pfxMax.top());
        int curMin = std::min(min, pfxMin.top());
        //cout << max << " " << min << endl;
        if(curMax - curMin <= c){
            valid = true;
            ans.append(to_string(i - m + 2) + "\n");
        }
    }
    if(!valid){
        ans.append("NONE\n");
    }
    cout << ans;

    return 0;
}



