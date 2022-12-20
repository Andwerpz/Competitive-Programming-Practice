#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1763A

//lets try to make the minimum number possible. Notice if all numbers have a certain bit, then the minimum
//number must have that bit. So the minimum number is just the and sum of all of the numbers. 

//and for the maximum, if any number has a given bit, then we can move it to the desginated maximum number, 
//so the maximum is just the or sum of the array. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        int max = 0;
        int min = 0;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        max = a[0];
        min = a[0];
        for(int i = 1; i < n; i++){
            max |= a[i];
            min &= a[i];
        }
        cout << (max - min) << "\n";
    }
    
    return 0;
}
