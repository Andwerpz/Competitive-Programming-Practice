#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1345C

//since we are dealing with infinity, we can use mod math to simulate wrapping. 

//lets simulate a subarray of n consecutive people. Their original values are k_i, and their new values are 
//k2_i. We just need to make sure that each of the values k2_i % n are unique out of those n consecutive people. 

int m(int a, int b){
    if(a >= 0){
        return a % b;
    }
    else{
        return (b - (abs(a) % b)) % b;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> nums(n, 0);
        vector<int> v(n, 0);
        for(int i = 0; i < n; i++){
            cin >> nums[i];
            v[m(i + nums[i], n)] ++;
        }
        bool isValid = true;
        for(int i : v){
            if(i != 1){
                isValid = false;
                break;
            }
        }
        cout << (isValid? "YES\n" : "NO\n");
    }
    
    return 0;
}
