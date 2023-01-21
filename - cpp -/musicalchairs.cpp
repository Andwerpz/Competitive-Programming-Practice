#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 01 C

//just do simulation. No need for fancy stuff. 

//notice that if a certain round will loop through all the chairs more than once, or a[i] > n, then we can just do
//a[i] = a[i] % n, where n is the amount of remaining people. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int p = 0;
    vector<bool> out(n);
    for(int i = n; i > 1; i--) {
        int cnt = (a[p] - 1) % i;
        //cout << p << "\n";
        for(int j = 0; j < cnt; j++) {
            p = (p + 1) % n;
            while(out[p]) {
                p = (p + 1) % n;
            }
        }
        //cout << "OUT : " << p << "\n";
        out[p] = true;
        p = (p + 1) % n;
        while(out[p]) {
            p = (p + 1) % n;
        }
    }
    int ans = -1;
    for(int i = 0; i < n; i++){
        if(!out[i]) {
            ans = i;
            break;
        }
    }
    cout << ans + 1 << "\n";
    
    return 0;
}
