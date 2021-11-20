
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

ll nb, ns, nc, pb, ps, pc, r, b, s, c;

bool isValid(ll amt){
    ll rb = b * amt;
    ll rs = s * amt;
    ll rc = c * amt;
    rb -= nb;
    rs -= ns;
    rc -= nc;
    rb = max(rb, 0ll);
    rs = max(rs, 0ll);
    rc = max(rc, 0ll);
    ll m = r;
    m -= rb * pb;
    m -= rs * ps;
    m -= rc * pc;
    if(m >= 0){
        return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string recipe;
    cin >> recipe;
    b = 0;
    s = 0;
    c = 0;
    cin >> nb >> ns >> nc >> pb >> ps >> pc >> r;
    for(int i = 0; i < recipe.size(); i++){
        char next = recipe[i];
        if(next == 'B'){
            b ++;
        }
        else if(next == 'S'){
            s ++;
        }
        else{
            c ++;
        }
    }
    ll ans = 0;
    ll low = 0;
    ll high = pow(10, 12);
    ll mid = low + (high - low) / 2;
    while(low <= high){
        if(isValid(mid)){
            low = mid + 1;
            ans = max(ans, mid);
        }
        else{
            high = mid - 1;
        }
        mid = low + (high - low) / 2;
    }
    cout << ans << endl;

    return 0;
}
