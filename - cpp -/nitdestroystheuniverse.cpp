#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1696B

//notice that using one operation we can set a subarray of numbers greater than zero all to 0. So obviously
//the minimum number of operations is equal to the amount of seperated subarrays of numbers greater than 0. 

//but theres a catch; we can spend exactly 2 operations to make all numbers equal to 0 regardless of the 
//contents of the array: do two operations over the entire array. 

//so the ans is min(2, num greater than 0 subarrays). 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        int ans = 0;
        bool zero = true;
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            if(zero){
                if(next != 0){
                    ans ++;
                    zero = false;
                }
            }
            else{
                if(next == 0){
                    zero = true;
                }
            }
        }
        cout << min(ans, 2) << "\n";
    }
    
    return 0;
}
