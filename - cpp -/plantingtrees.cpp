#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 05 C

//it is always optimal to plant the trees that take longer to grow first. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    int ans = 0;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    for(int i = 0; i < n; i++){
        ans = max(ans, a[i] + i + 2);
    }
    cout << ans << "\n";
    
    return 0;
}
