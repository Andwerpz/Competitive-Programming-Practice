#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1686A

//you can only make all the elements equal if there is an element that is equal to the mean of the array. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        int sum = 0;
        set<int> s;
        for(int i = 0; i < n; i++){
            int a;
            cin >> a;
            sum += a;
            s.insert(a);
        }
        if(sum % n != 0 || s.find(sum / n) == s.end()) {
            cout << "NO\n";
        }
        else{
            cout << "YES\n";
        }
    }
    
    return 0;
}
