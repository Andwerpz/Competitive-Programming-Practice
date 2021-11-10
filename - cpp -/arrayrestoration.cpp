
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1023D

//solved in java

//i don't know why, but i keep getting a out of bounds error on test case 6. Iterators in c++ are confusing.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    vector<int> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    vector<bool> v(q + 1, false);
    set<int> dict;
    dict.insert(1);
    vector<int> ans(n);
    bool isValid = true;
    bool hasZero = false;
    for(int i = 0; i < n; i++){
        if(nums[i] == 0){
            hasZero = true;
        }
        else {
            int cur = nums[i];
            ans[i] = cur;
            if(v[cur]){
                isValid = false;
                break;
            }
            if(dict.find(cur) == dict.end()){
                dict.insert(cur);
            }
            set<int>::iterator next = dict.end();
            next --;
            cout << "CUR: " << cur << endl;
            //cout << "NEXT: " << (*next) << endl;
            while(dict.size() != 0 && *next > cur){
                v[*next] = true;
                dict.erase(*next);
                next --;
            }
        }
        for(int i : dict){
            cout << i << " ";
        }
        cout << endl;
    }
    for(int i : dict){
        v[i] = true;
    }
    int maxUnvisited = 0;
    if(!v[q]){
        maxUnvisited = q;
    }
    for(int i = 0; i < n; i++){
        if(ans[i] == 0){
            if(maxUnvisited != 0){
                //cout << "MAX\n";
                ans[i] = maxUnvisited;
                maxUnvisited = 0;
            }
            else{
                //cout << "NOTMAX\n";
                ans[i] = max((i == 0? 0 : ans[i - 1]), (i == n - 1? 0 : ans[i + 1]));
            }
        }
    }
    if(maxUnvisited != 0){
        isValid = false;
    }
    if(isValid){
        cout << "YES\n";
        for(int i = 0; i < n; i++){
            cout << ans[i] << " ";
        }
        cout << endl;
    }
    else{
        cout << "NO\n";
    }

    return 0;
}



