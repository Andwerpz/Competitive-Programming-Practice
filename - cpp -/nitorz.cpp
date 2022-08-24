#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1696A

//after every operation, the value of z can only decrease. So the optimal stategy is to do only one
//operation, with z and the maximum in a. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, z;
        cin >> n >> z;
        int max = 0;
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            max = std::max(max, next | z);
        }
        cout << max << "\n";
    }
    
    return 0;
}
