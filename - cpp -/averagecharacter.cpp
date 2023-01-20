#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    getline(cin, s);
    int sum = 0;
    for(int i = 0; i < s.length(); i++) {
        sum += (int) s[i];
    }
    sum /= s.length();
    cout << ((char) sum) << "\n";
    
    return 0;
}
