#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1772D

//you want x to be the minimum possible. 

//if there is an i where a[i] < a[i - 1], then figure out the minimum possible x required to clear the inversion. 
//do this for all adjacent values, and figure out the maximum minimum x. 

//apply this x onto all of the values, and see if it's sorted. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n);
        bool isValid = true;
        int sub = 0;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            if(i == 0){
                continue;
            }
            if(a[i] >= a[i - 1]){
                continue;
            }
            int d = a[i - 1] - a[i];
            d = (d / 2) + d % 2;
            sub = max(d + a[i], sub);
        }
        for(int i = 0; i < n; i++){
            a[i] = abs(a[i] - sub);
            //cout << a[i] << " ";
            if(i == 0){
                continue;
            }
            if(a[i] < a[i - 1]){
                isValid = false;
            }
        }
        if(isValid) {
            cout << sub << "\n";
        }
        else {
            cout << "-1\n";
        }
    }
    
    return 0;
}
