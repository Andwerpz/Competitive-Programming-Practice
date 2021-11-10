
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codefoces - 1043D

//you can split the testimonies into groups of valid substrings. Given a substring of length n, there are (n * (n + 1)) / 2 possible ways to use prefixes and suffixes to get a 
//valid substring out of the current substring. 

//to get valid substrings, use one testimony as a baseline, and compare it to all others. 

//look in tutorial for more in depth explanation.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> nums(m);
    for(int i = 0; i < m; i++){
        nums[i] = vector<int>(n);
        for(int j = 0; j < n; j++){
            cin >> nums[i][j];
        }
    }
    map<int, pair<int, int>> dict;
    for(int i = 0; i < m; i++){
        if(i == 0){
            for(int j = 0; j < n; j++){
                dict.insert({nums[i][j], {j, 0}});
            }
        }
        else {
            int groupId = 0;
            int prev = -1;
            int prevGroup = -1;
            for(int j = 0; j < n; j++){
                int cur = nums[i][j];
                int next = dict.at(cur).first;
                int nextGroup = dict.at(cur).second;
                if(nextGroup != prevGroup || prev + 1 != next){
                    groupId ++;
                }
                dict.at(cur).second = groupId;
                prev = next;
                prevGroup = nextGroup;
                //cout << groupId << " ";
            }
            //cout << endl;
        }
        // for(int i = 1; i <= n; i++){
        //     cout << dict.at(i).first << " " << dict.at(i).second << ", ";
        // }
        // cout << endl;
    }
    vector<int> groups(100001);
    for(int i = 1; i <= n; i++){
        int nextGroup = dict.at(i).second;
        groups[nextGroup] ++;
    } 
    ll ans = 0;
    for(int i = 0; i < groups.size(); i++){
        ll next = groups[i];
        ans += (next * (next + 1)) / 2;
    }
    cout << ans << endl;

    return 0;
}



