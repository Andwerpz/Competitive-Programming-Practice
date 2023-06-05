#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1828C

//the problem is basically asking us how many distinct permutations there are of a where the condition is satisfied. 

//lets first sort arrays a and b. We notice that each a[i] has some prefix of b in which it can be placed, and that 
//as i grows bigger, the prefix grows longer. 

//the important observation is that if i < j, then a[i] has less options than a[j], and all the options a[i] has, a[j] has as well. 

//so, we can use a greedy approach. Go in ascending order and match each a[i] to an abitrary k, where a[i] > b[k]. Note that 
//the exact element you match an earlier i to k doesn't matter, so each element in a[i] has exactly numOptions - i options, 
//where numOptions is the number of elements in b where b[j] < a[i]. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n);
        vector<int> b(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        for(int i = 0; i < n; i++){
            cin >> b[i];
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        ll mod = 1e9 + 7;
        ll r = 0;
        ll ans = 1;
        for(int i = 0; i < n; i++){
            while(r != n && a[i] > b[r]) {
                r++;
            }
            ll amt = r - i;
            if(amt == 0){
                ans = 0;
                break;
            }
            ans *= amt;
            ans %= mod;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
