#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 1993B

//if there are only even or odd numbers, then you're done. 

//otherwise, observe that you can only use the operation to create more odd numbers, and
//at minimum, you'll have to use one operation for each even number. At most, you'll have to use
//1 extra operation, if you're unable to convert the greatest even number. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vi even(0), odd(0);
        for(int i = 0; i < n; i++){
            if(a[i] % 2 == 0){
                even.push_back(a[i]);
            }
            else {
                odd.push_back(a[i]);
            }
        }
        if(even.size() == 0 || odd.size() == 0){
            cout << "0\n";
            continue;
        }
        sort(a.begin(), a.end());
        bool needs_ex = false;
        sort(odd.begin(), odd.end());
        ll max_odd = odd[odd.size() - 1];
        sort(even.begin(), even.end());
        for(int i = 0; i < even.size(); i++){
            if(even[i] > max_odd){
                needs_ex = true;
                break;
            }
            max_odd += even[i];
        }
        cout << even.size() + needs_ex << "\n";
    }
    
    return 0;
}