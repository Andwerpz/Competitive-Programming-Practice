#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1772G

//you have to play against everyone once, before being able to play against a person twice. 

//the optimal strategy then is to play against everyone in ascending order. 
//with this ordering, you can gain the most rating at a time, and that allows you to beat more people. 

//at this point, it's just a matter of simulation. 

//this implementation can do with some improvements. 

ll ceilDiv(ll a, ll b){
    return (a / b) + (a % b != 0? 1 : 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    int cnt = 0;
    string s = "";
    while(t-- > 0){
        cnt ++;
        int n;
        ll x, y;
        cin >> n >> x >> y;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        // if(cnt == 4439){
        //     cout << n << " " << x << " " << y << endl;
        //     for(int i : a){
        //         cout << i << " ";
        //     }
        //     cout << endl;
        // }
        a.push_back(y);
        sort(a.begin(), a.end());
        //for each i, how many games does it take to make x >= a[i]
        ll ans = 0;
        int ptr = 0;
        bool isValid = true;
        for(int i = 0; i < n + 1; i++){
            //cout << "I : " << i << " " << x << " " << ptr << endl;
            if(x == y){
                break;
            }
            if(x >= a[i]) {
                continue;
            }
            ll maxAdd = min((ll) i - ptr, a[i] - x);
            ans += maxAdd;
            x += maxAdd;
            ptr += maxAdd;
            if(x == y){
                break;
            }
            if(x >= a[i]) {
                continue;
            }
            //reset ptr back to 0
            ans += n - ptr;
            x -= n - ptr;
            ptr = 0;
            ll diff = (i) - (n - i);
            if(diff <= 0){  //you'll either stay the same, or lose rating. 
                isValid = false;
                break;
            }
            ll maxInc = i;
            //want to know the minimum cycles before x + maxInc >= a[i] + 1;
            //x + b * diff >= a[i] - maxInc;
            //diff < maxInc, except when maxInc == n, then diff = maxInc, but in the loop, maxInc != n
            //cout << x << endl;
            ll b = ceilDiv(a[i] - maxInc - x, diff);
            if(a[i] - maxInc - x < 0) {
                b = 0;
            }
            ans += (ll) n * b;
            x += b * diff;
            maxAdd = min((ll) i - ptr, a[i] - x);
            ans += maxAdd;
            x += maxAdd;
            ptr += maxAdd;
            //x should now be equal to a[i]
            //cout << a[i] << " " << maxInc << " " << diff << endl;
            //cout << b << " " << x << endl;
        }
        if(!isValid){
            s += "-1\n";
            //cout << "-1\n";
            continue;
        }
        s += to_string(ans) + "\n";
        //cout << ans << "\n";
    }
    cout << s;
    
    return 0;
}
