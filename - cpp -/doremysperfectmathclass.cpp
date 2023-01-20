#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1764B

//if S contains 1, then we can generate all numbers from 1 - max(S). 

//if S initially doesn't contain 1, then in what situations can we use the operations to create a 1?
//lets say that S initially only consists of two elements, x and y; x > y. d = x - y. 

//if d == 1, then we can stop here, but if d != 1, then we can create x - d, and x - 2d, and so on. If the minimum number
//we can create is d again, then there is no way to make a smaller number, as x % d = 0, but if we can make a smaller
//number, then we can repeat with a new d. 

//the minimum d that we can create is the minimum number possible that we can create, and it is guaranteed to be the maximum 
//divisor of every other element in S. Thus, the minimum number possible is just equal to the gcd of all the elements in S. 

//the maximum amount of numbers in S is just max(S) / d. 

int gcd(int a, int b) {
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int g = a[0];
        for(int i = 1; i < n; i++){
            g = gcd(a[i], g);
        }
        cout << a[n - 1] / g << "\n";
    }
    
    return 0;
}
