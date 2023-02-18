#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 05 G

//simulation. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    cin >> s;
    bool isUp = s[0] == 'U';
    int upAns = 0;
    int downAns = 0;
    int ans = 0;
    for(int i = 1; i < s.length(); i++){
        bool wantUp = s[i] == 'U';
        if(wantUp != isUp){
            upAns ++;
        }
        isUp = true;
        if(!wantUp){
            upAns ++;
        }
    }
    isUp = s[0] == 'U';
    for(int i = 1; i < s.length(); i++){
        bool wantUp = s[i] == 'U';
        if(wantUp != isUp){
            downAns ++;
        }
        isUp = false;
        if(wantUp){
            downAns ++;
        }
    }
    isUp = s[0] == 'U';
    for(int i = 0; i < s.length(); i++){
        bool wantUp = s[i] == 'U';
        if(wantUp != isUp) {
            ans ++;
        }
        isUp = wantUp;
    }
    cout << upAns << "\n" << downAns << "\n" << ans << "\n";
    
    return 0;
}
