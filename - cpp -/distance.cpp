
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//Codeforces - 1612A

//you can separate into a few cases. 

//1. x, y == (0, 0):
//the answer has to be (0, 0)

//2. (x + y) % 2 == 1:
//this means that the distance from A to B is odd, and therefore, there exists no point C

//3. x % 2 == 0:
//together with the second statement, we can also say that y % 2 == 0. 
//this means that point c = (x / 2, y / 2).

//4. x % 2 == 1:
//this means that x and y are odd. We have to then divide them both, rounding down, and add 1 to either x or y. 
//c = (x / 2 + 1, y / 2).

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int x, y;
        cin >> x >> y;
        if(x + y == 0){
            cout << "0 0\n";
            continue;
        }
        if((x + y) % 2 == 1){
            cout << "-1 -1\n";
            continue;
        }
        if(x % 2 == 0){
            cout << (x / 2) << " " << (y / 2) << endl;
            continue;
        }
        cout << (x / 2 + 1) << " " << (y / 2) << endl;
    }
    
    return 0;
}
