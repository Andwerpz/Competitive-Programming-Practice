#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1858A

//all of the buttons of type c are going to be pressed first. 

//after that, if anna has more buttons, then she will win. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int a, b, c;
        cin >> a >> b >> c;
        bool annawin = false;
        if(c % 2 == 1){
            b --;
        }
        annawin = a > b;
        cout << (annawin? "First\n" : "Second\n");
    }
    
    return 0;
}
