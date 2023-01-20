#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1774A

//keep track of the running sum, and put + or - signs greedily to lower the absolute value. 

//note that the first '1' has to always be positive. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        int sum = 0;
        string s;
        cin >> s;
        if(s[0] == '1'){
            sum ++;
        }
        for(int i = 1; i < n; i++){
            if(s[i] == '0') {
                cout << "+";
            }
            else {
                if(sum == 0){
                    cout << "+";
                }
                else {
                    cout << "-";
                }
                sum = sum == 1? 0 : 1;
            }
        }
        cout << "\n";
    }
    
    return 0;
}
