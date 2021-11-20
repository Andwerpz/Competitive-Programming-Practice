
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//Codeforces - 1604B

//notice that if you split the array into subarrays of length 1, then the lis of all the subarrays will always be 1. 
//this means that if you have an even amount of subarrays, then the xor sum is 0. 

//if n is odd, then if there is ever a non-decreasing sequence inside the array, then you can just expand one subarray, while
//keeping it's lis 1. Then, you're left with an even amount of subarrays.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        bool decrease = false;
        int prev = 0;
        cin >> prev;
        for(int i = 0; i < n - 1; i++){
            int next;
            cin >> next;
            if(next <= prev){
                decrease = true;
            }
            prev = next;
        }
        cout << ((n % 2 == 0 || decrease)? "YES\n" : "NO\n");
    }

    return 0;
}
