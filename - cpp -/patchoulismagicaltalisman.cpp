#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1688B

//if the array has an odd number, then the ans is simply n - numOdd. 

//else, we need to create an odd number. Find the number in the array with the least amount of powers of two
//in it's prime factorization. Use that number to create our odd number. Then combine it with all others. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        int odd = 0;
        int minTwo = 1e9;
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            int two = 0;
            while(next % 2 == 0) {
                two ++;
                next /= 2;
            }
            if(two == 0){
                odd ++;
            }
            minTwo = min(minTwo, two);
        }
        if(odd == 0){
            cout << (n + minTwo - 1) << "\n";
        }
        else{
            cout << (n - odd) << "\n";
        }
    }
    
    return 0;
}
