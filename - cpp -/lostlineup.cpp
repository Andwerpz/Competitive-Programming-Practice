#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    cout << 1;
    vector<int> v (n-1);
    for(int i = 0; i < v.size(); i++) {
        int num;
        cin >> num;
        v[num] = i + 2;
    }
    for(int i = 0; i < v.size(); i++) {
        cout << " " << v[i];
    }
    
    return 0;
}
