#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 08 B

//brute force. There are only around 75 cubic numbers below 400,000. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<ll> a(75, 0);
    for(ll i = 1; i < a.size() + 1; i++){
        a[i - 1] = i * i * i;
    }
    vector<int> cnt(n + 1, 0);
    for(int i = 0; i < a.size(); i++){
        for(int j = i + 1; j < a.size(); j++){
            if(a[i] + a[j] > n){
                continue;
            }
            cnt[a[i] + a[j]] ++;
        }
    }
    int ans = -1;
    for(int i = n; i >= 1; i--){
        if(cnt[i] >= 2) {
            ans = i;
            break;
        }
    }
    if(ans == -1){
        cout << "none\n";
    }
    else {
        cout << ans << "\n";
    }
    
    return 0;
}
