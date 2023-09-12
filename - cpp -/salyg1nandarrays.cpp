#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1867E1 E2

//note that n and k are both divisible by 2. This is very useful when solving the problem. 

//if n % k == 0, then the problem is trivial to solve, because we can just partition the array into subarrays of length k. 
//otherwise, after partitioning the array, we'll have some leftover at the end, which size is equal to n % k. 

//then the problem becomes how do we account for this leftover portion? We can account for the leftover portion by using the 
//fact that the queries reverse the segment that they query. 

//consider the array [1, 2, 3, 4, 5, 6] with k = 4. We'll keep track of our current answer in 'ans'. 
//Since the actual values of the array don't matter, i'll just mark elements of the array that are factored into ans using
//'X', and ones that are not using 'O'. Initially, the array is :
//[O, O, O, O, O, O]
//we can query the first 4 elements into ans, and the array becomes
//[X, X, X, X, O, O]
//now we have to deal with the last 2 elements. If we query the range starting from index 2 (1 indexed), then the array becomes:
//[X, X, O, O, O, O]
//and we can just query the last 4 elements using 1 query. Note that although a query might cause an element to become unfactored
//from ans, the key point is that the query also flips elements in ans, and that makes it so that we can maintain some sort of prefix
//of values that are factored into ans. 

//this solution passes both the easy and hard versions. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n, k;
        cin >> n >> k;
        int rm = n;
        int ans = 0;
        while(rm > k){
            cout << "? " << (n - rm + 1) << endl;
            int next;
            cin >> next;
            ans ^= next;
            rm -= k;
        }
        if(rm != 0) {
            if(rm != k){
                int need = k - rm;
                int bal = (k - need) / 2;
                cout << "? " << (n - rm - bal - need + 1) << endl;
                int next;
                cin >> next;
                ans ^= next;
                rm = k;
            }
            cout << "? " << (n - k + 1) << endl;
            int next;
            cin >> next;
            ans ^= next;
            rm = 0;
        }
        cout << "! " << ans << endl;
    }
    
    return 0;
}
