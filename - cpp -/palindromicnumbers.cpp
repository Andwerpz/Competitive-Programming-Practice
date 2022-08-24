#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1700B

//if the first digit in the number is not equal to 9, then we can just add a number that 
//will make all the digits equal to 9. 

//else, we need to add a number that will make all the digits of the new number equal to 1. Note that this
//new number has to be 1 digit longer than both of the added numbers. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n + 1);
        for(int i = 0; i < n; i++){
            char c;
            cin >> c;
            a[i + 1] = c - '0';
        }
        vector<int> ans(n + 1);
        if(a[1] == 9){
            vector<bool> v(n + 1);
            for(int i = n; i >= 1; i--){
                if(i == n){
                    if(a[i] <= 1){
                        ans[i] = 1 - a[i];
                        v[i] = true;
                    }
                    else{
                        ans[i] = 11 - a[i];
                        v[i] = true;
                        v[i - 1] = true;
                    }
                }
                else{
                    if(a[i] == 0){
                        if(!v[i]){
                            ans[i] = 1;
                            v[i] = true;
                        }
                    }
                    else if(a[i] == 1){
                        if(!v[i]){
                            ans[i] = 0;
                            v[i] = true;
                        }
                        else{
                            ans[i] = 9;
                            v[i - 1] = true;
                        }
                    }
                    else{
                        if(!v[i]){
                            ans[i] = 11 - a[i];
                            v[i] = true;
                            v[i - 1] = true;
                        }
                        else{
                            ans[i] = 10 - a[i];
                            v[i - 1] = true;
                        }
                    }
                }
            }
        }
        else{
            for(int i = 1; i <= n; i++){
                ans[i] = 9 - a[i];
            }
        }
        for(int i = 1; i <= n; i++){
            cout << ans[i];
        }
        cout << "\n";
    }
    
    return 0;
}
