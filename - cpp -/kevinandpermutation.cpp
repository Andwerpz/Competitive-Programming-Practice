#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Week 6B

//you can split the array into two parts, one is the greater half, and the other is the lesser half. 
//create the answer array by alternating choosing the maximum element between the greater and lesser array 
//starting with the greater array. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        for(int i = 0; i < n; i++){
            if(i % 2 == 0) {
                cout << (n + 1) / 2 - i / 2 << " ";
            }
            else {
                cout << n - i / 2 << " ";
            }
        }
        cout << "\n";
    }
    
    return 0;
}
