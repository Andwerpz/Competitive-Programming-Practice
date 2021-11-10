
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1352F

//if you had to check whether the given input was valid before constructing the string, then the problem would be a little harder, but in this case
//where the inputs are guaranteed correct, the problem is trivial.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int n0, n1, n2;
        cin >> n0 >> n1 >> n2;
        if(n1 == 0 && n2 == 0){
            for(int i = 0; i <= n0; i++){
                cout << "0";
            }
            cout << endl;
        }
        else{
            if(n1 % 2 == 0 && n1 != 0){
                cout << "0";
                n1 --;
            }
            for(int i = 0; i <= n2; i++){
                cout << "1";
            }
            int which = 0;
            for(int i = 0; i < n1; i++){
                cout << which;
                which = which == 0? 1 : 0;
            }
            for(int i = 0; i < n0; i++){
                cout << "0";
            }
            cout << endl;
        }
    }

    return 0;
}



