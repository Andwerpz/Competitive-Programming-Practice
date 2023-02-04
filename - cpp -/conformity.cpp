#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 03 E

//since each student is taking maximum 5 courses, you can just use those 5 courses
//to make a unique hash. Since all courses are 3 digits, i chose to contatenate them into one long. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    map<ll, int> m;
    int n;
    cin >> n;
    int ans = 0;
    int mostPop = 0;
    for(int i = 0; i < n; i++){
        vector<ll> a(5);
        for(int j = 0; j < 5; j++){
            cin >> a[j];
        }
        sort(a.begin(), a.end());
        ll hash = 0;
        ll pow = 1;
        for(int j = 0; j < 5; j++){
            hash += a[j] * pow;
            pow *= 100;
        }
        if(m.find(hash) == m.end()) {
            m.insert({hash, 0});
        }
        m.find(hash) -> second ++;
        if(m.find(hash) -> second == mostPop) {
            ans += mostPop;
        }
        if(m.find(hash) -> second > mostPop) {
            mostPop = m.find(hash) -> second;
            ans = mostPop;
        }
    }
    cout << ans << "\n";
    
    return 0;
}
