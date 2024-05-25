#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1975C

//if there exists a subarray of 2 or more of the same element, then you can use the operation to spread out that element
//over the entire array. 

//then, note that doing the operation on a subarray of length >= 2 will assign that subarray equal to the median. Therefore, 
//the maximum value you can cover the array with is the value of the maximum median of any subarray in the array. 

//i did not prove this (google did), but the maximum median is guaranteed to appear in a subarray of length 2 or 3, 
//so you can just look through all of those. 

int calc_med(vector<int> a){
    sort(a.begin(), a.end());
    return a[(a.size() - 1) / 2];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        int max_med = 0;
        for(int i = 0; i < n; i++){
            if(i + 1 < n) {
                max_med = max(max_med, calc_med({a[i], a[i + 1]}));
            }
            if(i + 2 < n) {
                max_med = max(max_med, calc_med({a[i], a[i + 1], a[i + 2]}));
            }
        }
        cout << max_med << "\n";
    }
    
    return 0;
}