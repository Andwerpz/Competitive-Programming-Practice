#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1698A

//observe that a ^ a = 0, and 0 ^ a = a. 

//let s equal the xor sum of all elements in a including x. 
//s must be 0, since s can also be defined as x ^ x because a is constructed by first taking the xor sum of 
//the first n - 1 elements, and then setting the nth element equal to that xor sum. 

//if s = x ^ x, then in order to find x, we need to xor it again by x: x = s ^ x. 
//since s = 0, then any element in the array will satisfy s ^ x = x. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        int ans = 0;
        for(int i = 0; i < n; i++){
            cin >> ans;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
