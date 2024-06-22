
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1486 C1, C2

//ugh, interactive problem
// - 08/30/2021 andrew

//first, find the location of the second maximum. With this, if we query some subarray that includes the second maximum
//depending on the result, we know whether or not the maximum is also inside the subarray. If they give you the second
//maximum's index, then the maximum is inside, otherwise if they give you some random index, then it's not. 

//we can then first determine if the maximum is on the left or right side of the second maximum, and then do binary search
//on the left or right side to find the maximum. 

//this approach conveniently also solves the hard version. Idk what they were thinking when making the two versions.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    //first, find the index of the second maximum
    cout << "? " << 1 << " " << n << endl;
    int smax_ind;
    cin >> smax_ind;
    //then, check if the maximum is to the left or to the right
    bool to_right = true;
    if(smax_ind != 1){
        cout << "? " << 1 << " " << smax_ind << endl;
        int tmp;
        cin >> tmp;
        if(tmp == smax_ind) {
            to_right = false;
        }
    }
    if(to_right) {
        int low = smax_ind + 1;
        int high = n;
        int ans = high;
        while(low <= high) {
            int mid = low + (high - low) / 2;
            cout << "? " << smax_ind << " " << mid << endl;
            int tmp;
            cin >> tmp;
            if(tmp == smax_ind) {
                ans = min(ans, mid);
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }
        cout << "! " << ans << endl;
    }
    else {
        int low = 1;
        int high = smax_ind - 1;
        int ans = low;
        while(low <= high) {
            int mid = low + (high - low) / 2;
            cout << "? " << mid << " " << smax_ind << endl;
            int tmp;
            cin >> tmp;
            if(tmp == smax_ind) {
                ans = max(ans, mid);
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
        cout << "! " << ans << endl;
    }
    
    return 0;
}



