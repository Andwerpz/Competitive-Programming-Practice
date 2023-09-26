#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1870B

//if n is odd, then any operation we do will increase the xor sum of the array. Likewise, if n is even, then
//any operation we do will reduce the xor sum of the array. 

//thus, if n is odd, the minimum value is the initial xor sum, and the maximum value is the one generated after all 
//operations have been done. Vice versa for if n is odd. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<int> a(n);
        int xsum = 0;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            xsum = xsum ^ a[i];
        }
        vector<int> b(m);
        int rsum = 0;
        for(int i = 0; i < m; i++){
            cin >> b[i];
            rsum |= b[i];
        }
        int aans = xsum;
        int bans = xsum;
        if(n % 2 == 0){
            bans = xsum & ~rsum;
        }
        else {
            bans = xsum | rsum;
        }
        if(aans > bans) {
            swap(aans, bans);
        }
        cout << aans << " " << bans << "\n";
    }
    
    return 0;
}
