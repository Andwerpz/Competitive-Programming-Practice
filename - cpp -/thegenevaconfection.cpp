
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//DMOJ - CCC14S3

//just simulate the situation. If you can't pull directly from the mountain, then check if you can pull from the branch. 

//if you can't pull from either, then if the mountain still has carts, then move one to the branch, and check again. 

//if the mountain has no carts, then the input is invalid.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        stack<int> mountain;
        stack<int> branch;
        int n;
        cin >> n;
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            mountain.push(next);
        }
        bool isValid = true;
        int pointer = 1;
        while(true){
            if(mountain.size() != 0 && mountain.top() == pointer){
                mountain.pop();
                pointer ++;
            }
            else if(branch.size() != 0 && branch.top() == pointer){
                branch.pop();
                pointer ++;
            }
            else {
                if(mountain.size() != 0){
                    branch.push(mountain.top());
                    mountain.pop();
                }
                else{
                    isValid = false;
                    break;
                }
            }
            if(mountain.size() == 0 && branch.size() == 0){
                break;
            }
        }
        cout << (isValid? "Y\n" : "N\n");
    }

    return 0;
}



