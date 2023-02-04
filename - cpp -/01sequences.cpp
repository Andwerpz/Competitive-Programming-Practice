#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 03 A

//for each 0, you just need to count how many 1s precede it. The sum of all counts is the desired answer. 

//you can keep a count of how many 1s and ? marks there are, but the problem is that the question marks create
//multiple different versions of the binary string. 

//so lets say that there are k ?s. that means that you can generate 2^k bstrings. So for each 1, you increment the 1cnt by 2^k. 

//for each 0, you just need to add to ans the total amount of 1s. 

//with question marks, it's a little more complicated, half the time, they're 1 and half the time they're 0, so we can count them as
//half 1 half 0. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    cin >> s;
    int n = s.length();
    ll k = 0;
    ll kd4 = 1;
    ll kd2 = 1;
    ll kd1 = 1;
    ll mod = 1e9 + 7;
    ll ans = 0;
    ll oCnt = 0;
    ll qCnt = 0;
    ll cnt = 0;
    for(int i = 0; i < n; i++){
        if(s[i] == '?'){
            k ++;
        }
    }
    for(int i = 0; i < k; i++){
        kd1 *= 2;
        kd1 %= mod;
    }
    for(int i = 0; i < k - 1; i++){
        kd2 *= 2;
        kd2 %= mod;
    }
    for(int i = 0; i < k - 2; i++){
        kd4 *= 2;
        kd4 %= mod;
    }
    for(int i = 0; i < n; i++){
        if(s[i] == '1') {
            oCnt ++;
        }
        if(s[i] == '0') {
            ans += oCnt * kd1;
            ans %= mod;
            ans += qCnt * kd2;
            ans %= mod;
        }
        if(s[i] == '?') {
            ans += oCnt * kd2;
            ans %= mod;
            ans += qCnt * kd4;
            ans %= mod;
            qCnt ++;
        }
    }
    cout << ans << "\n";
    
    return 0;
}
