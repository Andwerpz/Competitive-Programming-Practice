#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1762D

//lets pick some random indices, a, b, c, and ask for gcd(a, b) and gcd(b, c)

//if gcd(a, b) == gcd(b, c), then b cannot be 0.
//if gcd(a, b) < gcd(b, c), then a cannot be 0, since gcd(b, c) is less than or equal to b
//by symmetry, if gcd(a, b) > gcd(b, c), then c cannot be 0. 

//just do it until you have 2 indices remaining, and then print both. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        set<int> s;
        for(int i = 1; i <= n; i++){
            s.insert(i);
        }
        while(s.size() != 2){
            auto ptr = s.begin();
            int a = *ptr;
            ptr ++;
            int b = *ptr;
            ptr ++;
            int c = *ptr;
            int g0, g1;
            cout << "? " << a << " " << b << endl;
            cin >> g0;
            cout << "? " << b << " " << c << endl;
            cin >> g1;
            if(g0 == g1){
                s.erase(b);
            }            
            else if(g0 < g1){
                s.erase(a);
            }
            else {
                s.erase(c);
            }
        }
        cout << "! " << *s.begin() << " " << *s.rbegin() << endl;
        int res;
        cin >> res;
    }
    
    return 0;
}
