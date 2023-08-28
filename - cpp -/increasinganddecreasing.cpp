#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1864A

//We can try to assign the maximum possible values to each element in the array starting from the last element. 

//if, when we get to the first element, the maximum possible value is less than x, then there is no way to construct
//the array. 

//otherwise, make sure to set the first element to x, and print the array. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int x, y, n;
        cin >> x >> y >> n;
        vector<int> a(n, 0);
        a[n - 1] = y;
        int inc = 1;
        for(int i = n - 2; i >= 0; i--){
            a[i] = a[i + 1] - inc;
            inc ++;
        }
        if(a[0] < x) {
            cout << "-1\n";
            continue;
        }
        a[0] = x;
        for(int i = 0; i < n; i++){
            cout << a[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
