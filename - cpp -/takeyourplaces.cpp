
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1556B

//tags: implementation... Really nailed that one

//the optimal strategy is to find the first out of place one, and swap it with the first one that is supposed to go in that place.

//to do this, you can just use two pointers.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> nums(n);
        vector<int> original(n);
        vector<int> odd;
        vector<int> even;
        int numEven = 0;
        int numOdd = 0;
        for(int i = 0; i < n; i++){
            cin >> nums[i];
            original[i] = nums[i];
            if(nums[i] % 2 == 0){
                numEven ++;
                even.push_back(nums[i]);
            }
            else{
                numOdd ++;
                odd.push_back(nums[i]);
            }
        }
        if(abs(numEven - numOdd) >= 2){
            cout << -1 << endl;
        }
        else if(n <= 2){
            cout << 0 << endl;
        }
        else{
            ll ans = -1;
            if(numEven >= numOdd){
                ans = 0;
                bool which = false; //false for even, true for odd
                int evenPointer = 0;
                int oddPointer = 0;
                while(nums[evenPointer] % 2 == 1){
                    evenPointer ++;
                }
                while(nums[oddPointer] % 2 == 0){
                    oddPointer ++;
                }
                for(int i = 0; i < n; i++){
                    //cout << evenPointer << " " << oddPointer << endl;
                    oddPointer = max(oddPointer, i);
                    evenPointer = max(evenPointer, i);
                    while(oddPointer != n && nums[oddPointer] % 2 == 0){
                                oddPointer ++;
                    }
                    while(evenPointer != n && nums[evenPointer] % 2 == 1){
                                evenPointer ++;
                    }
                    if(!which){
                        if(evenPointer == i){
                            evenPointer ++;
                            while(evenPointer != n && nums[evenPointer] % 2 == 1){
                                evenPointer ++;
                            }
                            
                        }
                        else{
                            ans += (ll) (evenPointer - i);
                            //cout << (evenPointer - i);
                            nums[i] = 2;
                            nums[evenPointer] = 1;
                            evenPointer ++;
                            while(evenPointer != n && nums[evenPointer] % 2 == 1){
                                evenPointer ++;
                            }
                        }
                    }
                    else{
                        if(oddPointer == i){
                            oddPointer ++;
                            while(oddPointer != n && nums[oddPointer] % 2 == 0){
                                oddPointer ++;
                            }
                        }
                        else{
                            ans += (ll) (oddPointer - i);
                            nums[i] = 1;
                            nums[oddPointer] = 2;
                            oddPointer ++;
                            while(oddPointer != n && nums[oddPointer] % 2 == 0){
                                oddPointer ++;
                            }
                        }
                    }
                    which = !which;
                }
            }
            if(numOdd >= numEven) {
                ll curAns = 0;
                for(int i = 0; i < n; i++){
                    nums[i] = original[i];
                }
                bool which = true; //false for even, true for odd
                int evenPointer = 0;
                int oddPointer = 0;
                while(nums[evenPointer] % 2 == 1){
                    evenPointer ++;
                }
                while(nums[oddPointer] % 2 == 0){
                    oddPointer ++;
                }
                for(int i = 0; i < n; i++){
                    //cout << evenPointer << " " << oddPointer << endl;
                    oddPointer = max(oddPointer, i);
                    evenPointer = max(evenPointer, i);
                    while(oddPointer != n && nums[oddPointer] % 2 == 0){
                                oddPointer ++;
                    }
                    while(evenPointer != n && nums[evenPointer] % 2 == 1){
                                evenPointer ++;
                    }
                    if(!which){
                        if(evenPointer == i){
                            evenPointer ++;
                            while(evenPointer != n && nums[evenPointer] % 2 == 1){
                                evenPointer ++;
                            }
                            
                        }
                        else{
                            curAns += (ll) (evenPointer - i);
                            //cout << (evenPointer - i);
                            nums[i] = 2;
                            nums[evenPointer] = 1;
                            evenPointer ++;
                            while(evenPointer != n && nums[evenPointer] % 2 == 1){
                                evenPointer ++;
                            }
                        }
                    }
                    else{
                        if(oddPointer == i){
                            oddPointer ++;
                            while(oddPointer != n && nums[oddPointer] % 2 == 0){
                                oddPointer ++;
                            }
                        }
                        else{
                            curAns += (ll) (oddPointer - i);
                            nums[i] = 1;
                            nums[oddPointer] = 2;
                            oddPointer ++;
                            while(oddPointer != n && nums[oddPointer] % 2 == 0){
                                oddPointer ++;
                            }
                        }
                    }
                    // for(int j = 0; j < n; j++){
                    //     cout << nums[j] << " ";
                    // }
                    // cout << endl;
                    which = !which;
                }
                if(ans == -1){
                    ans = curAns;
                }
                else{
                    ans = min(ans, curAns);
                }
            }
            
            
            //cout << ans << " " << curAns << endl;
            cout << ans << endl;
        }
    }

    return 0;
}



