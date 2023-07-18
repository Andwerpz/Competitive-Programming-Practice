#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1848D

//observe that we would always want to first increase the bonus some number of times, then use
//it for the remaining times. 

//first, consider a simpler problem. You can either use the discount, or add 1 to your bonus. In this case, the total
//bonus b can be modeled with the function: 
//b(x) = (s + x) * (k - x)
//x = number of days spent growing bonus
//s = initial bonus
//k = total number of days

//note that b(x) is a downwards parabola, which is bitonic. This means that we can do ternary search over b(x) to find the 
//maximum value. 

//now, back to the more complicated problem. First note that the sequence of last digits will either loop through the sequence
//[2, 4, 8, 6], or will go to 0. In the case that it goes to 0, we can just simulate it until it goes to 0, as it doesn't 
//make sense to continue to accumulate bonuses once it's 0. 

//for the looping case, we can notice that increasing the bonus 4 times will net a total of 20 increase to the bonus. Then, the total 
//discount is simply (s + 20 * x) * (k - 4 * x), where x is the number of times we increase the bonus 4 times. Then, we can do 
//ternary search 4 times, one time for each starting point in the cycle. 

ll calc(ll s, ll k, ll x){  
    //x is num days spent growing bonuses
    //s % 10 = 2
    //x % 4 = 0
    ll inc = (x / 4) * 20;
    ll ans = (s + inc) * (k - x);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // for(int i = 0; i < 10; i++){
    //     int x = i;
    //     set<int> v;
    //     while(v.find(x) == v.end()){
    //         v.insert(x);
    //         cout << x << " ";
    //         x = x + (x % 10);
    //         x %= 10;
    //     }
    //     cout << x << "\n";
    // }
    int t;
    cin >> t;
    while(t--) {
        ll s, k;
        cin >> s >> k;
        if(s % 10 == 0){
            ll ans = s * k;
            cout << ans << "\n";
            continue;
        }
        if(s % 10 == 5){
            ll ans = max(s * k, (s + 5) * (k - 1));
            cout << ans << "\n";
            continue;
        }
        ll ans = s * k;
        while(k > 0 && s % 10 != 2){
            s += s % 10;
            k --;
            ans = max(ans, s * k);
        }
        if(k == 0){
            cout << ans << "\n";
            continue;
        }
        //ternary search
        ll low = 0;
        ll high = k - (k % 4);
        while(high - low > 100){
            //cout << low << " " << high << "\n";
            ll m1 = low + (high - low) / 3;
            ll m2 = low + (high - low) * 2 / 3;
            m1 -= m1 % 4;
            m2 -= m2 % 4;
            ll v1 = calc(s, k, m1);
            ll v2 = calc(s, k, m2);
            if(v1 >= v2){
                high = m2;
            }
            else {
                low = m1;
            }
        }
        low = max(low - 100, (ll) 0);
        high = min(high + 100, k);
        vector<int> md = {2, 4, 8, 6};
        s += (low / 4) * 20;
        k -= low;
        for(ll i = low; i <= high; i++){
            ans = max(ans, s * k);
            s += md[i % 4];
            k --;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
