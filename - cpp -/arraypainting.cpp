#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1849D

//notice that we would want to pick blue tiles with the highest value to paint first, since the higher the value, 
//the more free tiles we can paint. 

//also note that if we have a contiguous subarray of non-zeroes, then we can paint all of them at the cost of 1 coin. 
//if the subarray has only 1s, then we can only paint one of the adjacent 0s to the subarray, but if it has at least one 2, 
//then we can paint both adjacent 0s. 

//so, the solution is just go from left to right, and find contiguous subarrays of non-zeroes. Paint all of them, and 
//choose to paint the left 0 before painting the right 0. After all the subarrays of non-zeroes are painted, then go and count
//the number of non-painted 0s, and add that amount to the answer. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<bool> v(n, false);
    int ans = 0;
    for(int i = 0; i < n;){
        if(a[i] == 0){
            i ++;
            continue;
        }
        ans ++;
        int r = i;
        bool has2 = false;
        while(r < n && a[r] != 0){
            if(a[r] == 2){
                has2 = true;
            }
            v[r] = true;
            r ++;
        }
        //cout << "LR : " << i << " " << r << "\n";
        if(has2) {
            if(i != 0){
                v[i - 1] = true;
            }
            if(r != n){
                v[r] = true;
            }
        }
        else {
            if(i != 0 && !v[i - 1]) {
                v[i - 1] = true;
            }
            else if(r != n && !v[r]) {
                v[r] = true;
            }
        }
        i = r;
    }
    for(int i = 0; i < n; i++){
        if(!v[i]){
            ans ++;
        }
    }
    cout << ans << "\n";
    
    return 0;
}
