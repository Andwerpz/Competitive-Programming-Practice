#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1845A

//casework:
//if x != 1, then we can just use n 1s. 
//if k == 1, then it is impossible to make n, since we can't pick any number. 
//if k == 2, then we can only choose 2, so check if n is even
//if n == 1, then we can't make it, because x = 1. 
//else, we can always make it using 2 and 3. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k, x;
        cin >> n >> k >> x;
        if(x != 1){
            cout << "YES\n";
            cout << n << "\n";
            for(int i = 0; i < n; i++){
                cout << "1 ";
            }
            cout << "\n";
            continue;
        }
        if(k == 1){
            cout << "NO\n";
            continue;
        }
        if(k == 2){
            if(n % 2 == 1){
                cout << "NO\n";
                continue;
            }
            cout << "YES\n";
            cout << n / 2 << "\n";
            for(int i = 0; i < n / 2; i++){
                cout << "2 ";
            }
            cout << "\n";
            continue;
        }
        if(n == 1){
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
        cout << n / 2 << "\n";
        for(int i = 0; i < n / 2; i++){
            if(i == 0){
                if(n % 2 == 1){
                    cout << "3 ";
                }
                else {
                    cout << "2 ";
                }
            }
            else {
                cout << "2 ";
            }
        }
        cout << "\n";
    }
    
    return 0;
}
