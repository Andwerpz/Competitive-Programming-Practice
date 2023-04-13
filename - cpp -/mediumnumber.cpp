#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1760A

//implementation. 

void swap(int& a, int& b){
    int tmp = a;
    a = b;
    b = tmp;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int a, b, c;
        cin >> a >> b >> c;
        if(c < a){
            swap(c, a);
        }
        if(c < b){
            swap(c, b);
        }
        if(b < a){
            swap(a, b);
        }
        cout << b << "\n";
    }
    
    return 0;
}
