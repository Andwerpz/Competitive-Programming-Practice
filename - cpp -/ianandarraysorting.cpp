#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1815A

//lets try to derive a third operation we can perform on the array. Suppose we have the array [0, 0, 0]. 
//we can then apply an increment operation to the last 2 elements, and a decrement to the first two, resulting in the array:
//[-1, 0, 1]. 

//if the number of elements are odd, then we can always make the last pair of elements non-decreasing by applying our new operation to 
//the end of the array. Then, we can make the second to last pair, then the third to last pair, and so on. 

//if the number of elements are odd, then we can always make the array non-decreasing. 

//if the number of elements are even, we can only make the array non-decreasing if the sum of
//the odd indexed elements are greater that or equal to the sum of the even indexed elements. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<ll> a(n, 0);
        auto read = [](ll a) {cin >> a; return a;};
        transform(a.begin(), a.end(), a.begin(), read);
        if(n % 2 == 1){
            cout << "YES\n";
            continue;
        }
        bool neg = true;
        auto alternate = [&](ll in){in *= neg? -1 : 1; neg ^= true; return in;};
        auto add = [](ll a, ll b) {return a + b;};
        transform(a.begin(), a.end(), a.begin(), alternate);
        ll diff = reduce(a.begin(), a.end(), (ll) 0, add);
        cout << (diff >= 0? "YES\n" : "NO\n");
    }
    
    return 0;
}
