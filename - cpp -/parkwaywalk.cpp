#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1697A

//since the total amount of energy needed to complete the walk is equal to the sum of all a_i, 
//the answer is max(sum - m, 0), max since if you have more energy than needed, you don't need to 
//get rid of the excess. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, m;
        cin >> n >> m;
        int sum = 0;
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            sum += next;
        }
        cout << max(sum - m, 0) << "\n";
    }
    
    return 0;
}
