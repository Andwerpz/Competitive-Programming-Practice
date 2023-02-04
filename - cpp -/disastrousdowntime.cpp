#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 03 F

//you just need to find the maximum amount of threads needed simulatenously, m, and the answer is ceil(m / k). 

//to do so, you can use a range pfx sum modification approach, where i is the time, and pfx[i] is the amount of
//threads currently running. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll ans = 0;
    int n;
    ll k;
    cin >> n >> k;
    vector<pair<int, int>> a(n * 2);
    for(int i = 0; i < n; i++){
        int t;
        cin >> t;
        a[i * 2].first = t;
        a[i * 2].second = 1;    //add request
        a[i * 2 + 1].first = t + 1000;
        a[i * 2 + 1].second = -1;    //remove request
    }
    sort(a.begin(), a.end());
    ll cur = 0;
    for(int i = 0; i < a.size(); i++) {
        cur += a[i].second;
        ans = max(ans, cur);
    }
    cout << (ans / k + (ans % k == 0? 0 : 1)) << "\n";
    
    return 0;
}
