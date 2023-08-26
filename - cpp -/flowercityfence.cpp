#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1862C

//we can compute the heights of the fence as if all the planks were laying horizontally, and then check if the two arrays are equal. 

//to avoid TLE, make sure that the maximum height of any plank in the fence does not exceed n. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        if(a[0] != n){
            cout << "NO\n";
            continue;
        }
        bool isValid = true;
        int ptr = n - 1;
        for(int i = 0; i < n; i++){
            int minh = i + 1;
            while(ptr >= 0 && a[ptr] < minh) {
                ptr --;
            }
            int amt = ptr + 1;
            //cout << "AMT : " << amt << "\n";
            if(amt != a[i]) {
                isValid = false;
            }
        }
        cout << (isValid? "YES\n" : "NO\n");
    }
    
    return 0;
}
