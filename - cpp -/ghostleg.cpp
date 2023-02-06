#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ICPC North America Qualifier 2022 D

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<int> v (n);
    for(int i = 0; i < n; i++) {
        v[i] = i + 1;
    }
    for(int i = 0; i < m; i++) {
        int swap;
        cin >> swap;
        int temp = v[swap-1];
        v[swap-1] = v[swap];
        v[swap] = temp;
    }   
    for(int x : v) {
        cout << x << "\n";
    }
    
    return 0;
}

