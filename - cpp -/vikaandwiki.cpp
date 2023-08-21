#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1848F

//note that if after 'x' operations, a becomes 0s, then it must be that x + 1 operations also makes a into 0s. 

//lets say that we do 2^t operations, where 0 <= t <= k. We can show that after these operations, a[i] = a[i] ^ a[(i + 2^t) % n]. 

//let's first find 'k', such that n = 2^k. Then, let's find the array after 2^(k - 1) operations have been performed. If the array
//still has a non-zero element, then we know that we need to perform more than 2^(k - 1) operations, so we take this new array 
//as our current array, and add to our answer 2^(k - 1). 

//if all the elements are 0, then we know that the number of operations is less than or equal to 2^(k - 1), so we do nothing for now. 

//decrement k, and repeat until k == 0. 

//the above solution is O(n * log(n)). It can be improved to O(n) by noticing that after we perform the 2^(k - 1) operations, we can
//shrink the array down to half size in both cases as in the case where there is a non-zero element, the new array must repeat itself after
//halfway, and in the case where all elements are 0, the original array must repeat halfway. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int ans = 0;
    while(n != 1) {
        //generate high / 2 operations
        vector<int> next(n / 2);
        bool isValid = true;
        for(int i = 0; i < n / 2; i++){
            next[i] = a[i] ^ a[(i + n / 2) % n];
            isValid &= next[i] == 0;
        }
        if(!isValid) {
            a = next;
            ans += n / 2;
        } 
        else {
            for(int i = 0; i < n / 2; i++){
                next[i] = a[i];
            }
            a = next;
        }
        n /= 2;
    }
    ans += a[0] == 0? 0 : 1;
    cout << ans << "\n";
    
    return 0;
}
