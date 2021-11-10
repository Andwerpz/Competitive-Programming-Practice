
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1044A

//first, by reading the problem statement, you can notice that all vertical blockers completely block off the entire board. We could probably make use of this. 

//another thing to notice is that horizontal blockers cannot share endpoints. This means that when you have 2 horizontal blockers on the same y level, they cannot
//"combine" to make a new longer blocker. This means that the y level doesn't matter, since the vertical blockers block the entire board anyways.

//we can use these two observations to conclude that the only important property of a horizontal blocker is that of blocking off the top within a given range of vertical blockers.
// a special case is if the horizontal blocker goes to 10^9, this means that you will have to remove it in order to continue.

//so to solve, we can iterate through the amount of vertical blockers we remove, while reducing the amount of horizontal blockers we have to remove.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<int> vert(n);
    vector<int> horizontal;  //to which vertical blocker does this horizontal one block off?
    for(int i = 0; i < n; i++){
        cin >> vert[i];
    }
    sort(vert.begin(), vert.end());
    for(int i = 0; i < m; i++){
        int x1, x2, y;
        cin >> x1 >> x2 >> y;
        if(x1 == 1){
            if(x2 == 1000000000){
                horizontal.push_back(n);
            }
            else{
                int low = 0;
                int high = n - 1;
                int mid = low + (high - low) / 2;
                int ans = -1;
                while(low <= high){
                    if(vert[mid] <= x2){
                        if(ans == -1){
                            ans = mid;
                        }
                        ans = max(ans, mid);
                        low = mid + 1;
                    }
                    else {
                        high = mid - 1;
                    }
                    mid = low + (high - low) / 2;
                }
                horizontal.push_back(ans);
            }
        }
    }
    sort(horizontal.begin(), horizontal.end());
    int pointer = 0;
    while(pointer != horizontal.size() && horizontal[pointer] == -1){
        pointer ++;
    }
    int ans = horizontal.size() - pointer;
    //cout << horizontal.size() << endl;
    for(int i = 0; i < vert.size(); i++){
        //cout << "LLOP\n";
        int nextVert = vert[i];
        while(pointer != horizontal.size() && horizontal[pointer] <= i){
            pointer ++;
        }
        int curAns = i + 1 + (horizontal.size() - pointer);
        ans = min(ans, curAns);
    }
    cout << ans << endl;

    return 0;
}



