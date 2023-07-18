#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1848C

//for a given i, lets say that x = a[i], and y = b[i]. 
//when we do the operation we assign x = y, and y = abs(x - y). 
//note that the sequence of numbers generated from a pair of x and y do not depend on any other x and y. 

//if x == 0 and y == 0, then x is always going to be 0. 

//else, we want to find the first time when x = 0. 
//simulating it takes too much time, as it can take up to around 10^9 operations for x to become 0, so we should find a
//smarter way. 

//1. check if x or y is 0. 
//1. simulate until x >= y. 
//2. if x > y * 2, do one operation, then go back to step 1
//3. now, x <= y * 2. note to decrease x by y * 2 requires 3 operations. Do as many of these as you can, then go to step 1

//once x or y is equal to 0, then it loops every 3 operations. Since we want to check if all a is 0 
//at once, we need to make sure that for all x y, the amount of operations % 3 is equal. 

int gcd(int a, int b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        vector<int> b(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        for(int i = 0; i < n; i++){
            cin >> b[i];
        }
        vector<int> m(3, 0);
        for(int i = 0; i < n; i++){
            int x = a[i];
            int y = b[i];
            if(x + y == 0){
                m[0] ++;
                m[1] ++;
                m[2] ++;
                continue;
            }
            int cnt = 0;
            int g = gcd(x, y);
            x /= g;
            y /= g;
            //cout << x << " " << y << " ";
            while(x != 0 && y != 0){
                while(x < y){
                    int tmp = abs(x - y);
                    x = y;
                    y = tmp;
                    cnt ++;
                }
                //x >= y
                int amt = x / (2 * y);
                if(amt == 0){
                    int tmp = abs(x - y);
                    x = y;
                    y = tmp;
                    cnt ++;
                }
                else {
                    x -= amt * 2 * y;
                    cnt += 3 * amt;
                }
            }
            //cout << "\n";
            if(y == 0){
                cnt ++;
            }
            m[cnt % 3] ++;
        }
        if(m[0] == n || m[1] == n || m[2] == n){
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
