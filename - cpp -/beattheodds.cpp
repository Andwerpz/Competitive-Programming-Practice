#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1691A

//in order to satisfy the condition, we just need to make the array only contain even
//or odd numbers. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        int even = 0;
        int odd = 0;
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            if(next % 2 == 0){
                even ++;
            }
            else{
                odd ++;
            }
        }
        cout << min(even, odd) << endl;
    }
    
    return 0;
}
