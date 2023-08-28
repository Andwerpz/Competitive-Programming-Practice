#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1864C

//instead of trying to go from x to 1, we can instead try to go from 1 to x. 

//let's denote i as the current value so far. 
//if the current value is i, then we can always double it, so lets double it until i * 2 > x. 

//next, we'll just add the greatest factor of two, t, such that i + t <= x. After we can't add anymore
//i has to be equal to x. 

//the answer is just the reverse sequence of generated i values. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int x;
        cin >> x;
        vector<int> ans(0);
        int ptr = 1;
        ans.push_back(1);
        int pow2 = 1;
        for(int i = 0; i < 30; i++){
            if(ptr + pow2 <= x) {
                ptr += pow2;
                ans.push_back(ptr);
            }
            pow2 *= 2;
        }
        pow2 /= 2;
        for(int i = 0; i < 30; i++){
            if(ptr + pow2 <= x) {
                ptr += pow2;
                ans.push_back(ptr);
            }
            pow2 /= 2;
        }
        cout << ans.size() << "\n";
        for(int i = ans.size() - 1; i >= 0; i--){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
