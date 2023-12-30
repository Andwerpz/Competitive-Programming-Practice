#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1894C

//We can just directly reverse the operations performed. The element which got last 'rotated' is going to always be
//the last element of the array. 

//Then, since k can be up to 10^9, we can't naively simulate this, so we can use the pideonhole principle and see
//if there is a loop from the last element. 

//One thing to keep in mind is that even if there is no loop, if the number of turns terminates before we get to an 
//invalid element, the informant could still be correct. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<int> v(n, false);
        bool is_valid = true;
        int ptr = n - 1;
        v[ptr] = true;
        while(true) {
            if(a[ptr] > n) {
                is_valid = false;
                break;
            }
            int next = (ptr - a[ptr] + n) % n;
            ptr = next;
            if(v[ptr]) {
                break;
            }
            v[ptr] = true;
            k --;
            if(k == 0){
                break;
            }
        }
        cout << (is_valid? "Yes" : "No") << "\n";
    }
    
    return 0;
}
