#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1828B

//given a value of k, it means that we can only sort indices i and j if i % k == j % k. 

//each element has a certain distance to it's correct location. Since the array is a permutation of 1 - n, it's pretty
//easy to determine this distance. 

//it also means that in order for a[i] to be sorted, k must divide the distance that a[i] has to it's desired position. 

//since we want to pick the maximum k to sort, we just need to find the gcd of all these distances. 

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
        int ans = 0;
        for(int i = 1; i <= n; i++){
            int next;
            cin >> next;
            int diff = abs(i - next);
            ans = gcd(ans, diff);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
