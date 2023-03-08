#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1794B

//lets say that you have two integers, a and b, and you want to make b not divisible by a. 
//if a != 1, then you can just add 1 to b. 

//so, if any a[i] == 1, then add 1 to it. Then do a second pass, adding 1 whenever the previous
//number can divide the current one. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n, 0);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            if(a[i] == 1){
                a[i] ++;
            }
        }
        for(int i = 1; i < n; i++){
            if(a[i] % a[i - 1] == 0){
                a[i] ++;
            }
        }
        for(int i = 0; i < n; i++){
            cout << a[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
