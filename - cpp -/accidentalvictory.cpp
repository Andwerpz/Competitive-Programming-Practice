
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

//1490E - Accidental Victory

//sort people in descending order. If a person with a tokens can win, then it is guaranteed that a person with b tokens, b >= a, can win. 

//if a person with a tokens cannot win, then it is guaranteed that a person with b, b < a, tokens cannot win.

//iterate through the people, and look for the first person that cannot win.

bool sortCol(const vector<long long> v1, const vector<long long> v2) {
    return v1[0] < v2[0];
}

int main()
{
    
    int t, n;
    //cout<<"input t";
    cin >> t;
    while(t-- > 0){
        //cout<<"input n";
        cin >> n;
        vector<vector<long long>> nums(n);
        long long sum = 0;
        for(int i = 0; i < n; i++){
            long long next;
            //cout<<"input next int";
            cin >> next;
            sum += next;
            nums[i].push_back(next);
            nums[i].push_back(i + 1);
            //cout << nums[i][0] << nums[i][1] << "\n";
        }
        sort(nums.begin(), nums.end(), sortCol);
        int stop = 1;
        for(int i = n - 1; i >= 0; i--){
            long long next = nums[i][0];
            if(i != n - 1){
                long long prev = nums[i + 1][0];
                if(sum < prev){
                    stop = i + 2;
                    break;
                }
            }
            sum -= next;
        }
        cout << (n - stop + 1) << "\n";
        //cout << n << "n " << stop << "stop"<< "\n";
        int i = stop;
        vector<int> ans;
        for(int i = stop - 1; i < n; i++){
            //cout << i << "i";
            ans.push_back(nums[i][1]);
        }
        sort(ans.begin(), ans.end());
        for(int i = 0; i < ans.size(); i++){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}



