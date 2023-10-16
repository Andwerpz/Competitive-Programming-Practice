#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//2023 Columbia University Local Contest B

//wait as long as possible before eating any watermelon. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    ll h;
    cin >> n >> h;
    vector<ll> a(n, 0);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    ll time = 1;
    h -= 1;
    if(a[0] != 0){
        h += a[0];
        a[0] = 0;
    }
    if(h == 0){
        cout << "NO\n";
        return 0;
    }
    for(int i = 1; i < n; i++){
        if(a[i] != 0){
            ll wait = (h - 1) / 2;
            h -= wait * 2;
            time += wait * 2;
            h += a[i] + time;
        }
        h --;
        time ++;
        //cout << "H : " << h << "\n";
        if(h > n){
            cout << "YES\n";
            return 0;
        }
        if(h == 0){
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES\n";
    
    return 0;
}
