#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1917A

//if the product is already negative or zero, there is nothing you can do to make it less.
//otherwise, the product is positive, in which case you just make one element zero. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        bool zero_exist = false;
        int nr_neg = 0;
        int pos_ind = -1;
        for(int i = 0; i < n; i++){
            int a;
            cin >> a;
            if(a < 0){
                nr_neg ++;
            }
            if(a > 0){
                if(pos_ind == -1){
                    pos_ind = i;
                }
            }
            if(a == 0){
                zero_exist = true;
            }
        }
        if(zero_exist) {
            cout << "0\n";
        }
        else if(nr_neg % 2 == 1){
            cout << "0\n";
        }
        else {
            cout << "1\n1 0\n";
        }
    }
    
    return 0;
}
