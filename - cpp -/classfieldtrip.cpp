#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ICPC North America Qualifier 2022 C

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string a, b; cin >> a >> b;
    string res = a + b;
    sort(res.begin(), res.end());

    cout << res << endl; 
    
    return 0;
}
