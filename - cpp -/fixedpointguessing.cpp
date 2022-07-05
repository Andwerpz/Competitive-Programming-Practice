#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1698D

//the structure of a is pretty convenient. 

//given a subarray, l - r, how do we determine if the answer lies inside it?

//for an element a_i, there are 3 cases:
//1: a_i is swapped with an element outside of subarray l - r. 
//2: a_i is swapped with an element inside of subarray l - r. 
//3: a_i is the stationary element. 

//notice that a_i of type 2 only show up in pairs. We can check for these by testing if l <= a_i <= r. 

//if there are an odd amount of a_i that satisfy l <= a_i <= r within l - r, then we know that the stationary element is in l - r. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        int l = 0;
        int r = n - 1;
        int mid = l + (r - l) / 2;
        while(l < r){
            cout << "? " << (l + 1) << " " << (mid + 1) << endl;
            int self = 0;
            for(int i = 0; i < (mid - l + 1); i++){
                int next;
                cin >> next;
                next--;
                if(l <= next && next <= mid){
                    self ++;
                }
            }
            if(self % 2 == 1){
                r = mid;
            }
            else{
                l = mid + 1;
            }
            mid = l + (r - l) / 2;
        }
        cout << "! " << (l + 1) << endl;
    }
    
    return 0;
}
