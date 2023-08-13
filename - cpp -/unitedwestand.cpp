#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1859A

//note that if x > y, then x can never be a divisor of y. 

//thus, we just need sort a in ascending order, and see if for any i, a[i] < a[i + 1]. 
//then, add all elements in the range 0 to i to a, and add elements i to n - 1 to b. 

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
        sort(a.begin(), a.end());
        bool isValid = false;
        int bind = -1;
        for(int i = 1; i < n; i++){
            if(a[i - 1] < a[i]) {
                isValid = true;
                bind = i;
                break;
            }
        }
        if(!isValid){
            cout << "-1\n";
            continue;
        }
        cout << bind << " " << (n - bind) << "\n";
        for(int i = 0; i < bind; i++){
            cout << a[i] << " ";
        }
        cout << "\n";
        for(int i = bind; i < n; i++){
            cout << a[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
