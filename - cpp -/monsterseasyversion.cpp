#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1784A

//sort the monsters in ascending order according to their healths. 

//a solution is always going to consist of some number of type 1 spells, followed by one cast of type two spells
//and then some number of type 1 spells. 

//note that with the type two spell, you want it to do the most damage possible, as if it does less damage, then that
//means that you'll have to cast more type one spells. 

//so, for each amount of type one spells, figure out the maximum prefix of monsters that you can kill with the type 2 spell

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<ll> a(n);
        ll sfx = 0;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            sfx += a[i];
        }
        sort(a.begin(), a.end());
        ll ans = -1;
        ll sum = 0;
        ll ptr = 0;
        for(int i = 0; i < n; i++){
            sfx -= a[i];
            if(a[i] - ptr >= 1){
                ll diff = a[i] - ptr - 1;
                ptr ++;
            }
            sum += a[i] - ptr;
            ll nextAns = sum;
            ll sub = (n - i - 1) * ptr;
            nextAns += sfx - sub;
            if(ans == -1){
                ans = nextAns;
            }
            ans = min(ans, nextAns);
        }
        cout << ans << "\n";
    }
    
    return 0;
}