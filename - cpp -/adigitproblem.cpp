
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll mod = 1000000007;
    cin >> n;
    set<int> digits;
    for(int i = 0; i < n; i++){
        int next;
        cin >> next;
        digits.insert(next);
    }
    string s;
    cin >> s;
    vector<int> k(s.length());
    for(int i = 0; i < k.size(); i++){
        k[i] = s[i] - '0';
    }
    ll ans = 0;
    vector<ll> dp;
    bool trump = false;
    ll power = 1;
    //reverse(k.begin(), k.end());
    for(int i = 0; i < k.size(); i++){
        ll cur = 0;
        for(int j = 0; j < 10; j++){
            if(digits.find(j) != digits.end()){
                cur += power;
                cur %= mod;
            }
            else if(i != 0){
                cur += dp[i - 1];
                cur %= mod;
            }
        }
        dp.push_back(cur);
        if(i != k.size() - 1){
            power *= 10;
            power %= mod;
        }
    }
    cout << "DP\n";
    for(auto i : dp){
        cout << i << " ";
    }
    cout << endl;
    for(int i = 0; i < k.size(); i++){
        cout << k[i] << " ";
        if(i == k.size() - 1){
            for(int j = 0; j <= k[i]; j++){
                if(digits.find(j) != digits.end() || trump){
                    ans ++;
                }
            }
        }
        else{
            ll power = 1;
            for(int j = 0; j < k.size() - i - 1; j++){
                power *= 10;
                power %= mod;
            }
            cout << power << " ";
            if(trump){
                for(int j = 0; j < k[i]; j++){
                    ans += power;
                    ans %= mod;
                }
            }
            else{
                for(int j = 0; j < k[i]; j++){
                    if(digits.find(j) != digits.end() && j != 0){
                        ans += power;
                        ans %= mod;
                    }
                    else{
                        ans += dp[i];
                        ans %= mod;
                    }
                }
                if(digits.find(k[i]) != digits.end()){
                    trump = true;
                    cout << "TRMP";
                }
            }
            
            
        }
        power *= 10;
        power %= mod;
    }
    cout << ans << endl;

    return 0;
}



