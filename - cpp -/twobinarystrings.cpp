#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1861B

//in order to make the two strings equal, they need to share the substring "01" at the same location. 
//note that if they do, then we can make the entire prefix equal to 0, and the entire suffix equal to 1. 

//if they do not share such a subarray in the same location, then it is impossible to make the two strings
//equal. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        string a, b;
        cin >> a >> b;
        bool isValid = false;
        for(int i = 1; i < a.size(); i++){
            if(a[i - 1] == '0' && a[i] == '1' && b[i - 1] == '0' && b[i] == '1'){
                isValid = true;
                break;
            }
        }
        cout << (isValid? "YES\n" : "NO\n");
    }
    
    return 0;
}
