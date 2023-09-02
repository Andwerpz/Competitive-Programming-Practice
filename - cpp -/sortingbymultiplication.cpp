#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codefoces - 1861D

//if a[i] <= a[i - 1], then we can fix a[i] by just multiplying the entire suffix [i, n) by some large value. 
//note that if we do this for all a[i] that are out of order, our result array is entirely positive. 

//note that the problem also allows you to multiply by negative numbers, the consequence being that any
//strictly descending subarray will be turned into a strictly ascending one when multiplied by -1. 

//thus, we want to figure out the minimum cost to turn the array into some sort of bitonic array, where 
//we have a strictly descending prefix, and a strictly ascending suffix. Then, we can just multiply the 
//prefix by -1, and have a strictly ascending array. 

//keep in mind that if the prefix size is 0, then we don't need to multiply by -1, saving us an operation. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        int ans = 0;
        for(int i = 1; i < n; i++){
            if(a[i] <= a[i - 1]){
                ans ++;
            }
        }
        int nrPos = ans;
        int nrNeg = 0;
        for(int i = 0; i < n; i++){
            if(i != n - 1 && a[i] >= a[i + 1]){
                nrPos --;
            }
            if(i != 0 && a[i] >= a[i - 1]){
                nrNeg ++;
            }
            ans = min(ans, nrPos + nrNeg + 1);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
