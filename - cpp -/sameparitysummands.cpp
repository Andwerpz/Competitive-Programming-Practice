
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1352B

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int n, k;
        cin >> n >> k;
        if(n % 2 == 0 && n / 2 >= k){
            cout << "YES\n";
            for(int i = 0; i < k - 1; i++){
                cout << "2 ";
                n -= 2;
            }
            cout << n << endl;
        }
        else if((n - (k - 1)) % 2 == 1 && n >= k){
            cout << "YES\n";
            for(int i = 0; i < k - 1; i++){
                cout << "1 ";
                n --;
            }
            cout << n << endl;
        }
        else{
            cout << "NO\n";
        }
    }

    return 0;
}



