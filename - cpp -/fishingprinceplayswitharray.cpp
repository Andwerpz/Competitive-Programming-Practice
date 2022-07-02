#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1696C

//define that a given array 'c' is fully expanded if you can't perform the 
//operation where you replace c_i with m copies of c_i / m. 

//if you fully expand a and b, and they are equivalent, then you can transform
//a into b using the given operations. 

//this is true because the two operations given are inverses of eachother. You can transform 
//c into fully expanded c, and fully expanded c back into the original c. Thus, if fully expanded a
//is equal to fully expanded b, then you can transform a into b. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        ll n, m, k;
        cin >> n >> m;
        vector<pair<ll, ll>> ga(0);
        vector<pair<ll, ll>> gb(0);
        ll prev = 0;
        for(int i = 0; i < n; i++){
            ll cur;
            cin >> cur;
            ll amt = 1;
            while(cur % m == 0){
                amt *= m;
                cur /= m;
            }
            if(cur != prev){
                ga.push_back({cur, 0});
                prev = cur;
            }
            ga[ga.size() - 1].second += amt;
        }
        cin >> k;
        prev = 0;
        for(int i = 0; i < k; i++){
            ll cur;
            cin >> cur;
            ll amt = 1;
            while(cur % m == 0){
                amt *= m;
                cur /= m;
            }
            if(cur != prev){
                gb.push_back({cur, 0});
                prev = cur;
            }
            gb[gb.size() - 1].second += amt;
        }
        bool isValid = ga.size() == gb.size();
        for(int i = 0; i < min(ga.size(), gb.size()); i++){
            //cout << ga[i] << " " << gb[i] << "\n";
            if(ga[i] != gb[i]){
                isValid = false;
            }
        }
        cout << (isValid? "Yes\n" : "No\n");
    }
    
    return 0;
}
